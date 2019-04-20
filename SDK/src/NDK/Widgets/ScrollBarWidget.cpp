
#include <NDK/Widgets/ScrollBarWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>

namespace Ndk
{
	Nz::Color ScrollBarWidget::s_buttonBaseColor{ 200, 200, 200 };
	Nz::Color ScrollBarWidget::s_buttonHoveredColor{ 220, 220, 220 };
	Nz::Color ScrollBarWidget::s_buttonPressedColor{ 255, 255, 255 };
	Nz::Color ScrollBarWidget::s_cursorColor{ 128, 128, 128 };
	Nz::Color ScrollBarWidget::s_cursorHoveredColor{ 150, 150, 150 };
	Nz::Color ScrollBarWidget::s_cursorPressedColor{ 180, 180, 180 };
	float ScrollBarWidget::s_cursorMoveSpeed{ 10.f };

	ScrollBarWidget::ScrollBarWidget(BaseWidget* parent) :
	BaseWidget{ parent },
	m_minValue{ 0 },
	m_maxValue{ 100 },
	m_value{ 0 },
	m_valueSize{ 10 },
	m_pressedButton{ PressedButton::none },
	m_orientation{ ScrollBarOrientation::ScrollBarOrientation_Vertical }
	{
		m_topButtonSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_topButtonSprite->SetColor(s_buttonBaseColor);
		m_topButtonSprite->SetTexture(Nz::TextureLibrary::Get("Ndk::ScrollBarWidget::scrollbarbutton"), false);

		m_bottomButtonSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_bottomButtonSprite->SetColor(s_buttonBaseColor);
		m_bottomButtonSprite->SetTexture(Nz::TextureLibrary::Get("Ndk::ScrollBarWidget::scrollbarbutton"), false);

		m_CursorSprite = Nz::Sprite::New(Nz::Material::New("Basic2D"));
		m_CursorSprite->SetColor(s_cursorColor);

		m_topButtonEntity = CreateEntity();
		m_topButtonEntity->AddComponent<Ndk::NodeComponent>().SetParent(this);
		m_topButtonEntity->AddComponent<Ndk::GraphicsComponent>().Attach(m_topButtonSprite);

		m_bottomButtonEntity = CreateEntity();
		m_bottomButtonEntity->AddComponent<Ndk::NodeComponent>().SetParent(this);
		m_bottomButtonEntity->AddComponent<Ndk::GraphicsComponent>().Attach(m_bottomButtonSprite);

		m_cursorEntity = CreateEntity();
		m_cursorEntity->AddComponent<Ndk::NodeComponent>().SetParent(this);
		m_cursorEntity->AddComponent<Ndk::GraphicsComponent>().Attach(m_CursorSprite);

		SetOrientation(m_orientation);
		Layout();
	}

	bool ScrollBarWidget::Initialize()
	{
		const Nz::UInt8 r_scrollbarButton[] =
		{
			#include <NDK/Resources/scrollbarbutton.png.h>
		};

		Nz::TextureRef scrollbarButtonTexture = Nz::Texture::LoadFromMemory(r_scrollbarButton, sizeof(r_scrollbarButton) / sizeof(r_scrollbarButton[0]));
		if (!scrollbarButtonTexture)
		{
			NazaraError("Failed to load embedded scrollbar Button");
			return false;
		}

		Nz::TextureLibrary::Register("Ndk::ScrollBarWidget::scrollbarbutton", std::move(scrollbarButtonTexture));
		return true;
	}

	void ScrollBarWidget::Uninitialize()
	{
		Nz::TextureLibrary::Unregister("Ndk::ScrollBarWidget::scrollbarbutton");
	}

	void ScrollBarWidget::OnLayout()
	{
		BaseWidget::OnLayout();

		Nz::Vector2f size = GetSize();

		size_t principalAxis = m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal ? 0 : 1;
		size_t otherAxis = m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal ? 1 : 0;

		Nz::Vector3ui buttonSpriteSize = m_topButtonSprite->GetMaterial()->GetDiffuseMap()->GetSize();

		Nz::Vector2f buttonSize{size[otherAxis], size[otherAxis] * buttonSpriteSize.y / buttonSpriteSize.x };
		m_topButtonSprite->SetSize(buttonSize);
		m_bottomButtonSprite->SetSize(buttonSize);
		buttonSize = GetButtonSize();

		if (m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal)
		{
			m_topButtonEntity->GetComponent<Ndk::NodeComponent>().SetPosition(buttonSize.x, 0);
			m_bottomButtonEntity->GetComponent<Ndk::NodeComponent>().SetPosition(size.x - buttonSize.x, buttonSize.y);
		}
		else
		{
			m_topButtonEntity->GetComponent<Ndk::NodeComponent>().SetPosition(buttonSize.x, buttonSize.y);
			m_bottomButtonEntity->GetComponent<Ndk::NodeComponent>().SetPosition(0, size.y - buttonSize.y);
		}

		float normalizedValue = (m_value - m_minValue) / (m_maxValue - m_minValue);
		float cursorArea = size[principalAxis] - 2 * buttonSize[principalAxis];
		Nz::Vector2f cursorPosition{ 0, 0 };
		cursorPosition[principalAxis] = buttonSize[principalAxis] + cursorArea * normalizedValue;
		m_cursorEntity->GetComponent<Ndk::NodeComponent>().SetPosition(cursorPosition);

		float normalizedValueSize = m_valueSize / (m_maxValue - m_minValue);
		Nz::Vector2f cursorSize;
		cursorSize[principalAxis] = normalizedValueSize * cursorArea;
		cursorSize[otherAxis] = size[otherAxis];
		m_CursorSprite->SetSize(cursorSize);

		UpdateRotation();
	}

	void ScrollBarWidget::UpdateRotation()
	{
		Nz::Vector3ui buttonSpriteSize = m_topButtonSprite->GetMaterial()->GetDiffuseMap()->GetSize();
		Nz::Vector2f size = GetSize();

		float width = ScrollBarOrientation::ScrollBarOrientation_Vertical ? size.x : size.y;

		Nz::Vector2f buttonSize{ width, width * buttonSpriteSize.y / buttonSpriteSize.x };

		if (m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal)
		{
			Nz::Matrix4f mat = Nz::Matrix4f::Rotate(Nz::Quaternionf(Nz::EulerAnglesf(0, 0, 90)));
			m_topButtonEntity->GetComponent<Ndk::GraphicsComponent>().UpdateLocalMatrix(m_topButtonSprite, mat);

			mat = Nz::Matrix4f::Rotate(Nz::Quaternionf(Nz::EulerAnglesf(0, 0, -90)));
			m_bottomButtonEntity->GetComponent<Ndk::GraphicsComponent>().UpdateLocalMatrix(m_bottomButtonSprite, mat);
		}
		else
		{
			Nz::Matrix4f mat = Nz::Matrix4f::Rotate(Nz::Quaternionf(Nz::EulerAnglesf(0, 0, 180)));
			m_topButtonEntity->GetComponent<Ndk::GraphicsComponent>().UpdateLocalMatrix(m_topButtonSprite, mat);

			m_bottomButtonEntity->GetComponent<Ndk::GraphicsComponent>().UpdateLocalMatrix(m_bottomButtonSprite, Nz::Matrix4f::Identity());
		}
	}

	void ScrollBarWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{
		PressedButton currentButton = GetButton(Nz::Vector2f(static_cast<float>(x), static_cast<float>(y)));

		m_topButtonSprite->SetColor(s_buttonBaseColor);
		m_bottomButtonSprite->SetColor(s_buttonBaseColor);
		m_CursorSprite->SetColor(s_cursorColor);

		if (currentButton == PressedButton::topButton)
			m_topButtonSprite->SetColor(s_buttonHoveredColor);
		if (currentButton == PressedButton::bottomButton)
			m_bottomButtonSprite->SetColor(s_buttonHoveredColor);
		if (currentButton == PressedButton::cursor)
			m_CursorSprite->SetColor(s_cursorHoveredColor);

		if (m_pressedButton == PressedButton::topButton)
			m_topButtonSprite->SetColor(s_buttonPressedColor);
		if (m_pressedButton == PressedButton::bottomButton)
			m_bottomButtonSprite->SetColor(s_buttonPressedColor);
		if (m_pressedButton == PressedButton::cursor)
			m_CursorSprite->SetColor(s_cursorPressedColor);

		if (m_pressedButton == PressedButton::cursor && (currentButton == PressedButton::topButton || currentButton == PressedButton::bottomButton))
			OnMouseExit();

		if (m_pressedButton != PressedButton::cursor)
			return;

		Nz::Vector2f size = GetSize();
		Nz::Vector2f buttonSize = GetButtonSize();

		size_t axis = m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal ? 0 : 1;
		float pos = static_cast<float>(m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal ? x : y);
		float normalizedPos = (pos - buttonSize[axis]) / (size[axis] - 2 * buttonSize[axis]);
		normalizedPos -= m_valueSize / (m_maxValue - m_minValue) / 2;

		SetValue(normalizedPos * (m_maxValue - m_minValue) + m_minValue);
	}

	void ScrollBarWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left)
		{
			m_pressedButton = GetButton(Nz::Vector2f(static_cast<float>(x), static_cast<float>(y)));
			OnMouseMoved(x, y, 0, 0);
		}
	}

	void ScrollBarWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left)
		{
			if (m_pressedButton == PressedButton::topButton)
				m_topButtonSprite->SetColor(s_buttonHoveredColor);
			if (m_pressedButton == PressedButton::bottomButton)
				m_bottomButtonSprite->SetColor(s_buttonHoveredColor);
			if (m_pressedButton == PressedButton::cursor)
				m_CursorSprite->SetColor(s_cursorHoveredColor);

			m_pressedButton = PressedButton::none;
		}
	}

	void ScrollBarWidget::OnMouseExit()
	{
		m_topButtonSprite->SetColor(s_buttonBaseColor);
		m_bottomButtonSprite->SetColor(s_buttonBaseColor);
		m_CursorSprite->SetColor(s_cursorColor);
	}

	ScrollBarWidget::PressedButton ScrollBarWidget::GetButton(Nz::Vector2f pos)
	{
		Nz::Vector2f size = GetSize();
		if (pos.x < 0 || pos.y < 0 || pos.x > size.x || pos.y > size.y)
			return PressedButton::none;

		size_t axis = m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal ? 0 : 1;
		Nz::Vector2f buttonSize = GetButtonSize();

		if (pos[axis] < buttonSize[axis])
			return PressedButton::topButton;
		if (pos[axis] > size[axis] - buttonSize[axis])
			return PressedButton::bottomButton;

		float normalizedValue = (m_value - m_minValue) / (m_maxValue - m_minValue);
		float normalizedValueSize = m_valueSize / (m_maxValue - m_minValue);
		float cursorArea = size[axis] - 2 * buttonSize[axis];

		pos[axis] -= buttonSize[axis];

		if (pos[axis] > normalizedValue * cursorArea && pos[axis] < (normalizedValue + normalizedValueSize) * cursorArea)
			return PressedButton::cursor;
		return PressedButton::none;
	}
}
