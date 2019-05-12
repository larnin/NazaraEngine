#include <NDK/Widgets/FoldableWidget.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <NDK/Components/GraphicsComponent.hpp>

namespace Ndk
{
	Nz::Color FoldableWidget::s_buttonBaseColor{ 200, 200, 200 };
	Nz::Color FoldableWidget::s_buttonHoveredColor{ 220, 220, 220 };
	Nz::Color FoldableWidget::s_buttonPressedColor{ 255, 255, 255 };
	float FoldableWidget::s_spacing{ 5 };

	FoldableWidget::FoldableWidget(BaseWidget* parent) :
	BaseWidget(parent),
	m_areaWidget(nullptr),
	m_folded(true),
	m_pressed(false)
	{
		m_buttonSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_buttonSprite->SetColor(s_buttonBaseColor);
		m_buttonSprite->SetTexture(Nz::TextureLibrary::Get("Ndk::ScrollBarWidget::scrollbarbutton"), false);
		Nz::Vector3ui buttonSpriteSize = m_buttonSprite->GetMaterial()->GetDiffuseMap()->GetSize();
		m_buttonSprite->SetTextureRect(Nz::Rectui((buttonSpriteSize.x - buttonSpriteSize.y) / 2, 0, buttonSpriteSize.y, buttonSpriteSize.y));

		m_buttonEntity = CreateEntity();
		m_buttonEntity->AddComponent<Ndk::NodeComponent>().SetParent(this);
		m_buttonEntity->AddComponent<Ndk::GraphicsComponent>().Attach(m_buttonSprite);

		m_textSprite = Nz::TextSprite::New();

		m_textEntity = CreateEntity();
		m_textEntity->AddComponent<NodeComponent>().SetParent(this);
		m_textEntity->AddComponent<GraphicsComponent>().Attach(m_textSprite, 1);

		SetFolded(m_folded);
	}

	void FoldableWidget::OnLayout()
	{
		Nz::Vector2f size = GetSize();
		Nz::Vector2f textSize(m_textSprite->GetBoundingVolume().obb.localBox.GetLengths());

		m_buttonSprite->SetSize(textSize.y, textSize.y);
		if (m_folded)
		{
			m_buttonEntity->GetComponent<GraphicsComponent>().UpdateLocalMatrix(m_buttonSprite, Nz::Matrix4f::Rotate(Nz::Quaternionf(Nz::EulerAnglesf(0, 0, -90))));
			m_buttonEntity->GetComponent<NodeComponent>().SetPosition(0, textSize.y);
		}
		else
		{
			m_buttonEntity->GetComponent<GraphicsComponent>().UpdateLocalMatrix(m_buttonSprite, Nz::Matrix4f::Identity());
			m_buttonEntity->GetComponent<NodeComponent>().SetPosition(0, 0);

			if (m_areaWidget != nullptr)
			{
				m_areaWidget->SetPosition(textSize.y, textSize.y + s_spacing);
				m_areaWidget->Resize(Nz::Vector2f(size.x - textSize.y, size.y - textSize.y - s_spacing));
			}
		}

		m_textEntity->GetComponent<NodeComponent>().SetPosition(textSize.y + s_spacing, 0);
	}

	void FoldableWidget::SetFolded(bool folded)
	{
		m_folded = folded;

		Nz::Vector2f size(m_textSprite->GetBoundingVolume().obb.localBox.GetLengths());

		size.x += size.y;

		if (!m_folded)
		{
			if (m_areaWidget != nullptr)
			{
				m_areaWidget->Show(true);
				Nz::Vector2f areaSize = m_areaWidget->GetSize();

				if (areaSize.x > size.x - size.y)
					size.x = areaSize.x + size.y;
				size.y += areaSize.y;
			}

			size.y += s_spacing;
		}
		else if (m_areaWidget != nullptr)
			m_areaWidget->Show(false);

		SetPreferredSize(size);
		SetMinimumSize(size);

		Layout();
	}

	void FoldableWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{
		Nz::Vector2f textSize(m_textSprite->GetBoundingVolume().obb.localBox.GetLengths());
		if (y > textSize.y)
			m_pressed = false;

		if (m_pressed)
			return;

		if (y > textSize.y)
			m_buttonSprite->SetColor(s_buttonBaseColor);
		else m_buttonSprite->SetColor(s_buttonHoveredColor);
	}

	void FoldableWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left)
		{
			Nz::Vector2f textSize(m_textSprite->GetBoundingVolume().obb.localBox.GetLengths());
			if (y < textSize.y)
			{
				m_pressed = true;
				SetFolded(!m_folded);
				m_buttonSprite->SetColor(s_buttonPressedColor);
			}
		}
	}

	void FoldableWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left)
		{
			m_pressed = false;
			OnMouseMoved(x, y, 0, 0);
		}
	}

	void FoldableWidget::OnMouseExit()
	{
		m_buttonSprite->SetColor(s_buttonBaseColor);
		m_pressed = false;
	}
}
