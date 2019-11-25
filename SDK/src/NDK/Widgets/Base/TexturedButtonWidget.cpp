
#include <NDK/Widgets/Base/TexturedButtonWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>

namespace Ndk
{
	TexturedButtonWidget::ButtonInfo::ButtonInfo()
		: color{ 255, 255, 255 }
		, textureCoords{ 0.f, 0.f, 1.f, 1.f }
	{

	}

	TexturedButtonWidget::TexturedButtonWidget(BaseWidget* parent)
		: BaseButtonWidget(parent)
		, m_textAlignment{ButtonTextAlignment_Centred}
		, m_textPosition{ButtonTextAlignment_Centred}
		, m_textMargin{16}
		, m_hovered{false}
		, m_currentButtonState{ButtonState_Idle}
	{
		int parentRenderOrderIndex = BaseWidget::GetRenderOrderIndex();

		m_buttonSprite = Nz::SlicedSprite::New();
		Nz::MaterialRef mat = Nz::Material::New("Translucent2D");
		mat->GetDiffuseSampler().SetAnisotropyLevel(10);
		m_buttonSprite->SetMaterial(mat);

		m_buttonEntity = CreateEntity();
		m_buttonEntity->AddComponent<NodeComponent>().SetParent(this);
		m_buttonEntity->AddComponent<GraphicsComponent>().Attach(m_buttonSprite, parentRenderOrderIndex + 1);

		m_textSprite = Nz::TextSprite::New();

		m_textEntity = CreateEntity();
		m_textEntity->AddComponent<NodeComponent>().SetParent(this);
		m_textEntity->AddComponent<GraphicsComponent>().Attach(m_textSprite, parentRenderOrderIndex + 2);

		Layout();
	}

	int TexturedButtonWidget::GetRenderOrderIndex() const
	{
		// the button sprite and the text at the top
		return BaseButtonWidget::GetRenderOrderIndex() + 2;
	}

	void TexturedButtonWidget::Layout()
	{
		BaseButtonWidget::Layout();

		m_buttonEntity->GetComponent<NodeComponent>().SetPosition(GetButtonPos());

		Nz::Vector2f size = GetSize();
		Nz::Boxf textBox = m_textEntity->GetComponent<GraphicsComponent>().GetAABB();

		if (m_textPosition == ButtonTextAlignment_Centred)
			SetButtonSize(size);
		else if (m_textPosition == ButtonTextAlignment_Left || m_textPosition == ButtonTextAlignment_Right)
			SetButtonSize(size - Nz::Vector2f(textBox.width + m_textMargin, 0));
		else if (m_textPosition == ButtonTextAlignment_Top || m_textPosition == ButtonTextAlignment_Down)
			SetButtonSize(size - Nz::Vector2f(0, textBox.height + m_textMargin));
		else SetButtonSize(size - Nz::Vector2f(textBox.width + m_textMargin, textBox.height + m_textMargin));

		m_textEntity->GetComponent<NodeComponent>().SetPosition(GetTextPos());

		m_currentButtonState = ButtonState_Idle;

		UpdateState();

		ButtonInfo & infos = m_buttonsDatas[m_currentButtonState];

		m_buttonSprite->SetTexture(infos.texture, false);
		m_buttonSprite->SetTextureCoords(infos.textureCoords);
		m_buttonSprite->SetColor(infos.color);
	}

	void TexturedButtonWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{
		if (!IsEnabled())
			return;

		Nz::Rectf box = GetButtonRect();
		bool hovered = box.Contains(Nz::Vector2f(static_cast<float>(x), static_cast<float>(y)));

		if (hovered != m_hovered)
		{
			m_hovered = hovered;
			if (!m_hovered && IsPressed())
				SetPressed(false, false);

			Layout();
		}
	}

	void TexturedButtonWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{
		if (!IsEnabled())
			return;

		OnMouseMoved(x, y, 0, 0);

		if (button == Nz::Mouse::Left && m_hovered)
		{
			SetPressed(true, true);
			Layout();
		}
	}

	void TexturedButtonWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{
		if (!IsEnabled())
			return;

		OnMouseMoved(x, y, 0, 0);

		if (button == Nz::Mouse::Left)
		{
			SetPressed(false, false);
			Layout();
		}
	}

	void TexturedButtonWidget::OnMouseExit()
	{
		m_hovered = false;

		if (IsPressed())
			SetPressed(false, false);

		Layout();
	}

	void TexturedButtonWidget::UpdateState()
	{
		if (!IsEnabled())
			m_currentButtonState = ButtonState_Disabled;
		else
		{
			if (IsPressed())
				m_currentButtonState = ButtonState_Pressed;
			else if (m_hovered)
				m_currentButtonState = ButtonState_Hovered;

			if (IsChecked())
			{
				if (m_hovered)
					m_currentButtonState = ButtonState_PressedHovered;
				else m_currentButtonState = ButtonState_Pressed;
			}
		}
	}

	void TexturedButtonWidget::UpdateSize()
	{
		Nz::Vector2f buttonSize(64, 64);
		Nz::Boxf textBox = m_textEntity->GetComponent<GraphicsComponent>().GetAABB();

		if (m_textPosition == ButtonTextAlignment_Centred)
		{
			SetPreferredSize(Nz::Vector2f(textBox.width + 2 * m_textMargin, textBox.height + 2 * m_textMargin));
			return;
		}

		if (m_textPosition == ButtonTextAlignment_Left || m_textPosition == ButtonTextAlignment_Right)
		{
			SetPreferredSize(Nz::Vector2f(buttonSize.x + m_textMargin + textBox.width, textBox.height + 2 * m_textMargin));
			return;
		}

		if (m_textPosition == ButtonTextAlignment_Left || m_textPosition == ButtonTextAlignment_Right)
		{
			SetPreferredSize(Nz::Vector2f(textBox.width + 2 * m_textMargin, buttonSize.y + m_textMargin + textBox.height));
			return;
		}

		SetPreferredSize(Nz::Vector2f(textBox.width + m_textMargin + buttonSize.x, textBox.height + m_textMargin + buttonSize.y));
	}

	Nz::Vector2f TexturedButtonWidget::GetTextPos() const
	{
		Nz::Vector2f buttonSize = GetButtonSize();
		Nz::Vector2f textPos = Nz::Vector2f::Zero();

		if (m_textPosition == ButtonTextAlignment_DownLeft || m_textPosition == ButtonTextAlignment_Down || m_textPosition == ButtonTextAlignment_DownRight)
			textPos.y += buttonSize.y + m_textMargin;
		if (m_textPosition == ButtonTextAlignment_TopRight || m_textPosition == ButtonTextAlignment_Right || m_textPosition == ButtonTextAlignment_DownRight)
			textPos.x += buttonSize.x + m_textMargin;

		return textPos + GetTextAlignmentOffset();
	}

	Nz::Vector2f TexturedButtonWidget::GetTextAlignmentOffset() const
	{
		Nz::Boxf textBox = m_textEntity->GetComponent<GraphicsComponent>().GetAABB();
		Nz::Vector2f buttonSize = GetButtonSize();

		Nz::Vector2f alignment = Nz::Vector2f::Zero();

		if (m_textPosition == ButtonTextAlignment_Top || m_textPosition == ButtonTextAlignment_Centred || m_textPosition == ButtonTextAlignment_Down)
		{
			if ((m_textAlignment == ButtonTextAlignment_Top || m_textAlignment == ButtonTextAlignment_Centred || m_textAlignment == ButtonTextAlignment_Down))
				alignment.x = (buttonSize.x - textBox.width) / 2;
			if (m_textAlignment == ButtonTextAlignment_Left || m_textAlignment == ButtonTextAlignment_TopLeft || m_textAlignment == ButtonTextAlignment_DownLeft)
				alignment.x = m_textPosition == ButtonTextAlignment_Centred ? m_textMargin : 0;
			if (m_textAlignment == ButtonTextAlignment_TopRight || m_textAlignment == ButtonTextAlignment_Right || m_textAlignment == ButtonTextAlignment_DownRight)
				alignment.x = buttonSize.x - textBox.width - (m_textPosition == ButtonTextAlignment_Centred ? m_textMargin : 0);
		}

		if (m_textPosition == ButtonTextAlignment_Left || m_textPosition == ButtonTextAlignment_Centred || m_textPosition == ButtonTextAlignment_Right)
		{
			if (m_textAlignment == ButtonTextAlignment_Left || m_textAlignment == ButtonTextAlignment_Centred || m_textAlignment == ButtonTextAlignment_Right)
				alignment.y = (buttonSize.y - textBox.height) / 2;
			if (m_textAlignment == ButtonTextAlignment_TopLeft || m_textAlignment == ButtonTextAlignment_Top || m_textAlignment == ButtonTextAlignment_TopRight)
				alignment.y = m_textPosition == ButtonTextAlignment_Centred ? m_textMargin : 0;
			if (m_textAlignment == ButtonTextAlignment_DownLeft || m_textAlignment == ButtonTextAlignment_Down || m_textAlignment == ButtonTextAlignment_DownRight)
				alignment.y = buttonSize.y - textBox.height - (m_textPosition == ButtonTextAlignment_Centred ? m_textMargin : 0);
		}

		return alignment;
	}

	Nz::Vector2f TexturedButtonWidget::GetButtonPos() const
	{
		Nz::Boxf textBox = m_textEntity->GetComponent<GraphicsComponent>().GetAABB();

		Nz::Vector2f buttonPos = Nz::Vector2f::Zero();

		if (m_textPosition == ButtonTextAlignment_Left || m_textPosition == ButtonTextAlignment_TopLeft || m_textPosition == ButtonTextAlignment_DownLeft)
			buttonPos.x += textBox.width + m_textMargin;
		if (m_textPosition == ButtonTextAlignment_Top || m_textPosition == ButtonTextAlignment_TopLeft || m_textPosition == ButtonTextAlignment_TopRight)
			buttonPos.y += textBox.height + m_textMargin;

		return buttonPos;
	}

	Nz::Rectf TexturedButtonWidget::GetButtonRect() const
	{
		Nz::Vector2f pos(m_buttonEntity->GetComponent<NodeComponent>().GetPosition(Nz::CoordSys_Local));
		Nz::Vector2f size = m_buttonSprite->GetSize();
		return Nz::Rectf(pos.x, pos.y, size.x, size.y);
	}
}
