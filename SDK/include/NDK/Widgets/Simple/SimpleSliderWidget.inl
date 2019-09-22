#include <NDK/Widgets/Simple/SimpleSliderWidget.hpp>

namespace Ndk
{
	inline void SimpleSliderWidget::SetSliderTexture(Nz::TextureRef texture, SliderOrientation orientation, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_sliderDatas[orientation][i].texture = texture;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture on this ButtonState");

		m_sliderDatas[orientation][state].texture = texture;

		UpdatePreferedSize();
	}

	inline void SimpleSliderWidget::SetSliderTextureCoord(const Nz::Rectf & coord, SliderOrientation orientation, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_sliderDatas[orientation][i].textureCoords = coord;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this ButtonState");

		m_sliderDatas[orientation][state].textureCoords = coord;

		UpdatePreferedSize();
	}

	inline void SimpleSliderWidget::SetSliderTextureRect(const Nz::Rectui & rect, SliderOrientation orientation, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
			{
				NazaraAssert(m_sliderDatas[orientation][i].texture, "No texture defined on this ButtonState");

				Nz::Vector3ui texSize = m_sliderDatas[orientation][i].texture->GetSize();

				m_sliderDatas[orientation][i].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
					static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);
			}

			UpdatePreferedSize();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this State");

		NazaraAssert(m_sliderDatas[orientation][state].texture, "No texture defined on this State");

		Nz::Vector3ui texSize = m_sliderDatas[orientation][state].texture->GetSize();

		m_sliderDatas[orientation][state].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);

		UpdatePreferedSize();
	}

	inline void SimpleSliderWidget::SetSliderColor(const Nz::Color & color, SliderOrientation orientation, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_sliderDatas[orientation][i].color = color;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any color on this ButtonState");

		m_sliderDatas[orientation][state].color = color;

		Layout();
	}

	inline void SimpleSliderWidget::SetBackgroundTexture(Nz::TextureRef texture, SliderOrientation orientation, bool disabled)
	{
		if (disabled)
			m_backDisabled[orientation].texture = texture;
		else m_back[orientation].texture = texture;

		Layout();
	}

	inline void SimpleSliderWidget::SetBackgroundTextureCoord(const Nz::Rectf & coord, SliderOrientation orientation, bool disabled)
	{
		if (disabled)
			m_backDisabled[orientation].textureCoords = coord;
		else m_back[orientation].textureCoords = coord;

		Layout();
	}

	inline void SimpleSliderWidget::SetBackgroundTextureRect(const Nz::Rectui & rect, SliderOrientation orientation, bool disabled)
	{
		TextureInfo & infos = disabled ? m_backDisabled[orientation] : m_back[orientation];

		NazaraAssert(infos.texture, "No texture defined on this ButtonState");

		Nz::Vector3ui texSize = infos.texture->GetSize();

		infos.textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);

		Layout();
	}

	inline void SimpleSliderWidget::SetBackgroundColor(const Nz::Color & color, SliderOrientation orientation, bool disabled)
	{
		if (disabled)
			m_backDisabled[orientation].color = color;
		else m_back[orientation].color = color;

		Layout();
	}

	inline void SimpleSliderWidget::SetBackgroundMargin(float margin)
	{
		m_backMargin = margin;
	}

	inline void SimpleSliderWidget::SetMoveSpeed(float speed)
	{
		m_moveSpeed = speed;
	}

	inline void SimpleSliderWidget::EnableTextValue(bool enabled)
	{
		if (enabled == m_textEnabled)
			return;

		m_textEnabled = enabled;

		UpdateTextSize();
	}

	inline void SimpleSliderWidget::SetTextFont(const Nz::FontRef & font)
	{
		m_textFont = font;

		UpdateTextSize();
	}

	inline void SimpleSliderWidget::SetTextCharacterSize(unsigned int size)
	{
		m_textStyle = size;

		UpdateTextSize();
	}

	inline void SimpleSliderWidget::SetTextStyle(Nz::TextStyleFlags style)
	{
		m_textStyle = style;

		UpdateTextSize();
	}

	inline void SimpleSliderWidget::SetTextColor(Nz::Color color)
	{
		m_textColor = color;

		Layout();
	}

	inline void SimpleSliderWidget::SetTextPosition(ButtonTextAlignment alignment)
	{
		m_textPosition = alignment;

		UpdateTextSize();
	}


	inline void SimpleSliderWidget::SetTextMagin(float margin)
	{
		m_textMargin = margin;

		UpdatePreferedSize();
	}

	inline void SimpleSliderWidget::SetTextPrecision(unsigned int precision)
	{
		m_textPrecision = precision;

		UpdateTextSize();
	}

	inline Nz::TextureRef SimpleSliderWidget::GetSliderTexture(SliderOrientation orientation, ButtonState state) const
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any texture in that state");

		return m_sliderDatas[orientation][state].texture;
	}

	inline Nz::Rectf SimpleSliderWidget::GetSliderTextureCoord(SliderOrientation orientation, ButtonState state) const
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any texture coords in that state");

		return m_sliderDatas[orientation][state].textureCoords;
	}

	inline Nz::Color SimpleSliderWidget::GetSliderColor(SliderOrientation orientation, ButtonState state) const
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any color in that state");

		return m_sliderDatas[orientation][state].color;
	}

	inline Nz::TextureRef SimpleSliderWidget::GetBackgroundTexture(SliderOrientation orientation, bool disabled) const
	{
		if (disabled)
			return m_backDisabled[orientation].texture;
		else return m_back[orientation].texture;
	}

	inline Nz::Rectf SimpleSliderWidget::GetBackgroundTextureCoord(SliderOrientation orientation, bool disabled) const
	{
		if (disabled)
			return m_backDisabled[orientation].textureCoords;
		else return m_back[orientation].textureCoords;
	}

	inline Nz::Color SimpleSliderWidget::GetBackgroundColor(SliderOrientation orientation, bool disabled) const
	{
		if (disabled)
			return m_backDisabled[orientation].color;
		else return m_back[orientation].color;
	}

	inline float SimpleSliderWidget::GetBackgroundMargin() const
	{
		return m_backMargin;
	}


	inline float SimpleSliderWidget::GetMoveSpeed() const
	{
		return m_moveSpeed;
	}

	inline bool SimpleSliderWidget::IsTextValueEnabled() const
	{
		return m_textEnabled;
	}

	inline Nz::FontRef SimpleSliderWidget::GetTextFont() const
	{
		return m_textFont;
	}

	inline unsigned int SimpleSliderWidget::GetTextCharacterSize() const
	{
		return m_textCharacterSize;
	}

	inline Nz::TextStyleFlags SimpleSliderWidget::GetTextStyle() const
	{
		return m_textStyle;
	}

	inline Nz::Color SimpleSliderWidget::GetTextColor() const
	{
		return m_textColor;
	}

	inline ButtonTextAlignment SimpleSliderWidget::GetTextPosition() const
	{
		return m_textPosition;
	}

	inline float SimpleSliderWidget::GetTextMargin() const
	{
		return m_textMargin;
	}


	inline unsigned int SimpleSliderWidget::GetTextPrecision() const
	{
		return m_textPrecision;
	}

	inline bool SimpleSliderWidget::IsPressed() const
	{
		return m_pressed;
	}

	inline bool SimpleSliderWidget::IsBackgroundPressed() const
	{
		return m_backgroundPressed;
	}


	inline bool SimpleSliderWidget::IsHovered() const
	{
		return m_hovered;
	}

	inline void SimpleSliderWidget::SetPressed(bool pressed)
	{
		if (m_pressed == pressed)
			return;

		m_pressed = pressed;

		OnPress(pressed);
	}

	inline void SimpleSliderWidget::SetBackgroundPressed(bool pressed)
	{
		if (m_backgroundPressed == pressed)
			return;

		m_backgroundPressed = pressed;

		OnBackgroundPress(pressed);
	}

	inline void SimpleSliderWidget::SetHovered(bool hovered)
	{
		if (m_hovered == hovered)
			return;

		m_hovered = hovered;

		OnHover(hovered);
	}

	inline Nz::Vector2f SimpleSliderWidget::GetTextPos() const
	{
		Nz::Vector2f size = GetSize();

		Nz::Vector2f pos(0, 0);

		switch (m_textPosition)
		{
		case ButtonTextAlignment_Left:
			pos.y = (size.y - m_textSize.y) / 2.f;
			break;
		case ButtonTextAlignment_DownLeft:
			pos.y = size.y - m_textSize.y;
			break;
		case ButtonTextAlignment_Down:
			pos.x = (size.x - m_textSize.x) / 2.f;
			pos.y = size.y - m_textSize.y;
			break;
		case ButtonTextAlignment_DownRight:
			pos.x = size.x - m_textSize.x;
			pos.y = size.y - m_textSize.y;
			break;
		case ButtonTextAlignment_Right:
			pos.x = size.x - m_textSize.x;
			pos.y = (size.y - m_textSize.y) / 2.f;
			break;
		case ButtonTextAlignment_TopRight:
			pos.x = size.x - m_textSize.x;
			break;
		case ButtonTextAlignment_Top:
			pos.x = (size.x - m_textSize.x) / 2.f;
			break;
		case ButtonTextAlignment_Centred:
			pos.x = (size.x - m_textSize.x) / 2.f;
			pos.y = (size.y - m_textSize.y) / 2.f;
			break;
		case ButtonTextAlignment_TopLeft:
		default:
			break;
		}

		return pos;
	}

	inline Nz::Vector2f SimpleSliderWidget::GetSliderPos() const
	{
		if (!m_textEnabled)
			return Nz::Vector2f::Zero();

		Nz::Vector2f pos(0, 0);

		if (m_textPosition == ButtonTextAlignment_TopLeft || m_textPosition == ButtonTextAlignment_TopRight || m_textPosition == ButtonTextAlignment_Top)
			pos.y = m_textMaxSize.y + m_textMargin;

		if (m_textPosition == ButtonTextAlignment_TopLeft || m_textPosition == ButtonTextAlignment_DownLeft || m_textPosition == ButtonTextAlignment_Left)
			pos.x = m_textMaxSize.x + m_textMargin;

		return pos;
	}

	inline Nz::Vector2f SimpleSliderWidget::GetSliderSize() const
	{
		Nz::Vector2f size = GetSize();

		if (!m_textEnabled)
			return size;

		if (m_textPosition == ButtonTextAlignment_TopLeft || m_textPosition == ButtonTextAlignment_TopRight || m_textPosition == ButtonTextAlignment_Top
			|| m_textPosition == ButtonTextAlignment_DownLeft || m_textPosition == ButtonTextAlignment_DownRight || m_textPosition == ButtonTextAlignment_Down)
			size.y -= m_textMaxSize.y + m_textMargin;
		if (size.y < 1)
			size.y = 1;
		if (m_textPosition == ButtonTextAlignment_TopLeft || m_textPosition == ButtonTextAlignment_DownLeft || m_textPosition == ButtonTextAlignment_Left
			|| m_textPosition == ButtonTextAlignment_TopRight || m_textPosition == ButtonTextAlignment_DownRight || m_textPosition == ButtonTextAlignment_Right)
			size.x -= m_textMaxSize.x + m_textMargin;
		if (size.x < 1)
			size.x = 1;

		return size;
	}
}
