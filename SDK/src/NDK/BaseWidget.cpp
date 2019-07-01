// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Nazara Development Kit"
// For conditions of distribution and use, see copyright notice in Prerequisites.hpp

#include <NDK/BaseWidget.hpp>
#include <NDK/Canvas.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <NDK/World.hpp>
#include <algorithm>

namespace Ndk
{
	/*!
	* \ingroup NDK
	* \class Ndk::BaseWidget
	* \brief Abstract class serving as a base class for all widgets
	*/

	/*!
	* \brief Constructs a BaseWidget object using another widget as its parent
	*
	* \param parent Parent widget, must be valid and attached to a canvas
	*
	* Constructs a BaseWidget object using another widget as a base.
	* This will also register the widget to the canvas owning the top-most widget.
	*/
	BaseWidget::BaseWidget(BaseWidget* parent) :
	BaseWidget()
	{
		NazaraAssert(parent, "Invalid parent");
		NazaraAssert(parent->GetCanvas(), "Parent has no canvas");

		m_canvas = parent->GetCanvas();
		m_widgetParent = parent;
		m_world = m_canvas->GetWorld();

		RegisterToCanvas();
	}

	/*!
	* \brief Frees the widget, unregistering it from its canvas
	*/
	BaseWidget::~BaseWidget()
	{
		UnregisterFromCanvas();
	}

	/*!
	* \brief Clears keyboard focus if and only if this widget owns it.
	*/
	void BaseWidget::ClearFocus()
	{
		if (IsRegisteredToCanvas())
			m_canvas->ClearKeyboardOwner(m_canvasIndex);
	}

	/*!
	* \brief Destroy the widget, deleting it in the process.
	*
	* Calling this function immediately destroys the widget, freeing its memory.
	*/
	void BaseWidget::Destroy()
	{
		NazaraAssert(this != m_canvas, "Canvas cannot be destroyed by calling Destroy()");

		m_widgetParent->DestroyChild(this); //< This does delete us
	}

	/*!
	* \brief Enable or disables the widget background.
	*/
	void BaseWidget::EnableBackground(bool enable)
	{
		if (m_backgroundEntity.IsValid() == enable)
			return;

		if (enable)
		{
			m_backgroundSprite = Nz::Sprite::New();
			m_backgroundSprite->SetColor(m_backgroundColor);
			m_backgroundSprite->SetMaterial(Nz::Material::New((m_backgroundColor.IsOpaque()) ? "Basic2D" : "Translucent2D")); //< TODO: Use a shared material instead of creating one everytime

			m_backgroundEntity = CreateEntity();
			m_backgroundEntity->AddComponent<GraphicsComponent>().Attach(m_backgroundSprite, -1);
			m_backgroundEntity->AddComponent<NodeComponent>().SetParent(this);

			BaseWidget::Layout(); // Only layout background
		}
		else
		{
			m_backgroundEntity.Reset();
			m_backgroundSprite.Reset();
		}
	}

	/*!
	* \brief Checks if this widget has keyboard focus
	* \return true if widget has keyboard focus, false otherwise
	*/
	bool BaseWidget::HasFocus() const
	{
		if (!IsRegisteredToCanvas())
			return false;

		return m_canvas->IsKeyboardOwner(m_canvasIndex);
	}

	void BaseWidget::Resize(const Nz::Vector2f& size)
	{
		// Adjust new size
		Nz::Vector2f newSize = size;
		newSize.Maximize(m_minimumSize);
		newSize.Minimize(m_maximumSize);

		m_size = newSize;

		Layout();

		for (auto & child : m_children)
			child->Resize(child->m_preferredSize);
	}

	void BaseWidget::SetBackgroundColor(const Nz::Color& color)
	{
		m_backgroundColor = color;

		if (m_backgroundSprite)
		{
			m_backgroundSprite->SetColor(color);
			m_backgroundSprite->GetMaterial()->Configure((color.IsOpaque()) ? "Basic2D" : "Translucent2D"); //< Our sprite has its own material (see EnableBackground)
		}
	}

	void BaseWidget::SetCursor(Nz::SystemCursor systemCursor)
	{
		m_cursor = systemCursor;

		if (IsRegisteredToCanvas())
			m_canvas->NotifyWidgetCursorUpdate(m_canvasIndex);
	}

	void BaseWidget::SetFocus()
	{
		if (IsRegisteredToCanvas())
			m_canvas->SetKeyboardOwner(m_canvasIndex);
	}

	void BaseWidget::Show(bool show)
	{
		if (m_visible != show)
		{
			m_visible = show;

			if (!m_visibleInHierarchy)
				return;

			if (m_visible)
				RegisterToCanvas();
			else
				UnregisterFromCanvas();

			for (WidgetEntity& entity : m_entities)
				entity.handle->Enable(show);

			for (const auto& widgetPtr : m_children)
				widgetPtr->SetVisibleInHerarchy(show);
		}
	}

	void BaseWidget::SetVisibleInHerarchy(bool visible)
	{
		if (visible != m_visibleInHierarchy)
		{
			m_visibleInHierarchy = visible;

			if (!m_visible)
				return;

			if (m_visibleInHierarchy)
				RegisterToCanvas();
			else
				UnregisterFromCanvas();

			for (WidgetEntity& entity : m_entities)
				entity.handle->Enable(visible);

			for (const auto& widgetPtr : m_children)
				widgetPtr->SetVisibleInHerarchy(visible);
		}
	}

	void BaseWidget::SetEnabled(bool enabled)
	{
		if (m_enabled != enabled)
		{
			m_enabled = enabled;

			if (!m_enabledInHierarchy)
				return;

			for (const auto& widgetPtr : m_children)
				widgetPtr->SetEnabledInHerarchy(enabled);
		}
	}

	void BaseWidget::SetEnabledInHerarchy(bool enabled)
	{
		if (enabled != m_enabledInHierarchy)
		{
			m_enabledInHierarchy = enabled;

			if (!m_enabled)
				return;

			for (const auto& widgetPtr : m_children)
				widgetPtr->SetEnabledInHerarchy(enabled);
		}
	}

	const Ndk::EntityHandle& BaseWidget::CreateEntity()
	{
		const EntityHandle& newEntity = m_world->CreateEntity();
		newEntity->Enable(m_visible);

		m_entities.emplace_back();
		WidgetEntity& widgetEntity = m_entities.back();
		widgetEntity.handle = newEntity;

		return newEntity;
	}

	void BaseWidget::DestroyEntity(Entity* entity)
	{
		auto it = std::find_if(m_entities.begin(), m_entities.end(), [&](const WidgetEntity& widgetEntity) { return widgetEntity.handle == entity; });
		NazaraAssert(it != m_entities.end(), "Entity does not belong to this widget");

		m_entities.erase(it);
	}

	void BaseWidget::Layout()
	{
		if (m_backgroundEntity)
			m_backgroundSprite->SetSize(m_size.x, m_size.y);

		UpdatePositionAndSize();
	}

	void BaseWidget::InvalidateNode()
	{
		Node::InvalidateNode();

		UpdatePositionAndSize();
	}

	int BaseWidget::GetRenderOrderIndex() const
	{
		if (m_widgetParent != nullptr)
			return m_widgetParent->GetRenderOrderIndex();
		return 0;
	}

	bool BaseWidget::IsFocusable() const
	{
		return false;
	}

	void BaseWidget::OnFocusLost()
	{
	}

	void BaseWidget::OnFocusReceived()
	{
	}

	bool BaseWidget::OnKeyPressed(const Nz::WindowEvent::KeyEvent& key)
	{
		return false;
	}

	void BaseWidget::OnKeyReleased(const Nz::WindowEvent::KeyEvent& /*key*/)
	{
	}

	void BaseWidget::OnMouseEnter()
	{
	}

	void BaseWidget::OnMouseMoved(int /*x*/, int /*y*/, int /*deltaX*/, int /*deltaY*/)
	{
	}

	void BaseWidget::OnMouseButtonPress(int /*x*/, int /*y*/, Nz::Mouse::Button /*button*/)
	{
	}

	void BaseWidget::OnMouseButtonRelease(int /*x*/, int /*y*/, Nz::Mouse::Button /*button*/)
	{
	}

	void BaseWidget::OnMouseExit()
	{
	}

	void BaseWidget::OnTextEntered(char32_t /*character*/, bool /*repeated*/)
	{
	}

	void BaseWidget::DestroyChild(BaseWidget* widget)
	{
		auto it = std::find_if(m_children.begin(), m_children.end(), [widget] (const std::unique_ptr<BaseWidget>& widgetPtr) -> bool
		{
			return widgetPtr.get() == widget;
		});

		NazaraAssert(it != m_children.end(), "Child widget not found in parent");

		m_children.erase(it);
	}

	void BaseWidget::DestroyChildren()
	{
		m_children.clear();
	}

	void BaseWidget::RegisterToCanvas()
	{
		NazaraAssert(!IsRegisteredToCanvas(), "Widget is already registered to canvas");

		m_canvasIndex = m_canvas->RegisterWidget(this);
	}

	void BaseWidget::UnregisterFromCanvas()
	{
		if (IsRegisteredToCanvas())
		{
			m_canvas->UnregisterWidget(m_canvasIndex);
			m_canvasIndex = InvalidCanvasIndex;
		}
	}

	void BaseWidget::UpdatePositionAndSize()
	{
		if (IsRegisteredToCanvas())
			m_canvas->NotifyWidgetBoxUpdate(m_canvasIndex);

		Nz::Vector2f widgetPos = Nz::Vector2f(GetPosition());
		Nz::Vector2f widgetSize = GetSize();

		Nz::Recti fullBounds(Nz::Rectf(widgetPos.x, widgetPos.y, widgetSize.x, widgetSize.y));
		for (WidgetEntity& widgetEntity : m_entities)
		{
			const Ndk::EntityHandle& entity = widgetEntity.handle;
			if (entity->HasComponent<GraphicsComponent>())
				entity->GetComponent<GraphicsComponent>().SetScissorRect(fullBounds);
		}
	}

	void BaseWidget::Update(float elapsedTime)
	{

	}

	void BaseWidget::ChildResized()
	{
		if(m_widgetParent == nullptr)
			Resize(m_preferredSize);
		else m_widgetParent->ChildResized();
	}
}
