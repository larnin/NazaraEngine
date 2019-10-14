#include <NDK/Widgets/Simple/SimpleScrollBarWidget.hpp>

namespace Ndk
{
	inline void SimpleScrollBarWidget::SetButtonTexture(Nz::TextureRef texture, ScrollBarButton button, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_buttonsDatas[button][i].texture = texture;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture on this ButtonState");

		m_buttonsDatas[button][state].texture = texture;

		UpdatePreferedSize();
	}

	inline void SimpleScrollBarWidget::SetButtonTextureCoord(const Nz::Rectf & coord, ScrollBarButton button, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_buttonsDatas[button][i].textureCoords = coord;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this ButtonState");

		m_buttonsDatas[button][state].textureCoords = coord;

		UpdatePreferedSize();
	}

	inline void SimpleScrollBarWidget::SetButtonTextureRect(const Nz::Rectui & rect, ScrollBarButton button, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
			{
				NazaraAssert(m_buttonsDatas[button][i].texture, "No texture defined on this ButtonState");

				Nz::Vector3ui texSize = m_buttonsDatas[button][i].texture->GetSize();

				m_buttonsDatas[button][i].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
					static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);
			}

			UpdatePreferedSize();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this State");

		NazaraAssert(m_buttonsDatas[button][state].texture, "No texture defined on this State");

		Nz::Vector3ui texSize = m_buttonsDatas[button][state].texture->GetSize();

		m_buttonsDatas[button][state].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);

		UpdatePreferedSize();
	}

	inline void SimpleScrollBarWidget::SetButtonColor(const Nz::Color & color, ScrollBarButton button, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_buttonsDatas[button][i].color = color;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any color on this ButtonState");

		m_buttonsDatas[button][state].color = color;

		UpdatePreferedSize();
	}

	inline void SimpleScrollBarWidget::SetCenterButtonSliceMargin(float size)
	{
		m_centerButtonSprite->SetSliceMargin(size);
	}

	inline void SimpleScrollBarWidget::SetCenterButtonSliceMargin(float top, float down, float left, float right)
	{
		m_centerButtonSprite->SetSliceMargin(top, down, left, right);
	}

	inline void SimpleScrollBarWidget::SetCenterButtonSliceMargin(unsigned int top, unsigned int down, unsigned int left, unsigned int right)
	{
		m_centerButtonSprite->SetSliceMargin(top, down, left, right);
	}

	inline void SimpleScrollBarWidget::SetCenterButtonSliceMargin(unsigned int size)
	{
		m_centerButtonSprite->SetSliceMargin(size);
	}

	inline void SimpleScrollBarWidget::SetBackgroundTexture(Nz::TextureRef texture, SliderOrientation orientation)
	{
		TextureInfo & info = orientation == SliderOrientation_Horizontal ? m_horizontalBackgroundDatas : m_verticalBackgroundDatas;

		info.texture = texture;

		Layout();
	}

	inline void SimpleScrollBarWidget::SetBackgroundTextureCoord(const Nz::Rectf & coord, SliderOrientation orientation)
	{
		TextureInfo & info = orientation == SliderOrientation_Horizontal ? m_horizontalBackgroundDatas : m_verticalBackgroundDatas;

		info.textureCoords = coord;

		Layout();
	}

	inline void SimpleScrollBarWidget::SetBackgroundTextureRect(const Nz::Rectui & rect, SliderOrientation orientation)
	{
		TextureInfo & info = orientation == SliderOrientation_Horizontal ? m_horizontalBackgroundDatas : m_verticalBackgroundDatas;

		NazaraAssert(info.texture, "No texture defined on this orientation");

		Nz::Vector3ui texSize = info.texture->GetSize();

		info.textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);
	}

	inline void SimpleScrollBarWidget::SetBackgroundColor(const Nz::Color & color, SliderOrientation orientation)
	{
		TextureInfo & info = orientation == SliderOrientation_Horizontal ? m_horizontalBackgroundDatas : m_verticalBackgroundDatas;

		info.color = color;

		Layout();
	}

	inline void SimpleScrollBarWidget::SetMoveSpeed(float speed)
	{
		m_moveSpeed = speed;
	}

	inline void SimpleScrollBarWidget::SetMoveButtonSpeed(float speed)
	{
		m_moveButtonSpeed = speed;
	}

	inline Nz::TextureRef SimpleScrollBarWidget::GetButtonTexture(ScrollBarButton button, ButtonState state)
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any texture in that state");

		return m_buttonsDatas[button][state].texture;
	}

	inline Nz::Rectf SimpleScrollBarWidget::GetButtonTextureCoord(ScrollBarButton button, ButtonState state)
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any texture coord in that state");

		return m_buttonsDatas[button][state].textureCoords;
	}

	inline Nz::Color SimpleScrollBarWidget::GetButtonColor(ScrollBarButton button, ButtonState state)
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any color in that state");

		return m_buttonsDatas[button][state].color;
	}

	inline Nz::TextureRef SimpleScrollBarWidget::GetBackgroundTexture(SliderOrientation orientation)
	{
		if (orientation == SliderOrientation_Horizontal)
			return m_horizontalBackgroundDatas.texture;
		return m_verticalBackgroundDatas.texture;
	}

	inline Nz::Rectf SimpleScrollBarWidget::GetBackgroundTextureCoord(SliderOrientation orientation)
	{
		if (orientation == SliderOrientation_Horizontal)
			return m_horizontalBackgroundDatas.textureCoords;
		return m_verticalBackgroundDatas.textureCoords;
	}

	inline Nz::Color SimpleScrollBarWidget::GetBackgroundColor(SliderOrientation orientation)
	{
		if (orientation == SliderOrientation_Horizontal)
			return m_horizontalBackgroundDatas.color;
		return m_verticalBackgroundDatas.color;
	}

	inline bool SimpleScrollBarWidget::IsPressed() const
	{
		return m_pressed;
	}

	inline bool SimpleScrollBarWidget::IsBackgroundPressed() const
	{
		return m_backgroundPressed;
	}

	inline bool SimpleScrollBarWidget::IsButtonLessPressed() const
	{
		return m_buttonLessPressed;
	}

	inline bool SimpleScrollBarWidget::IsButtonMorePressed() const
	{
		return m_buttonMorePressed;
	}

	inline bool SimpleScrollBarWidget::IsHovered() const
	{
		return m_hovered;
	}

	inline bool SimpleScrollBarWidget::IsButtonLessHovered() const
	{
		return m_buttonLessHovered;
	}

	inline bool SimpleScrollBarWidget::IsButtonMoreHovered() const
	{
		return m_buttonMoreHovered;
	}

	inline float SimpleScrollBarWidget::GetMoveSpeed() const
	{
		return m_moveSpeed;
	}

	inline float SimpleScrollBarWidget::GetButtonMoveSpeed() const
	{
		return m_moveButtonSpeed;
	}

	inline void SimpleScrollBarWidget::SetPressed(bool pressed)
	{
		if (m_pressed == pressed)
			return;

		m_pressed = pressed;
		if (pressed)
			m_currentPressedButton = PressedButton_Center;
		else if (m_currentPressedButton == PressedButton_Center)
			m_currentPressedButton = PressedButton_None;

		OnPress(m_pressed);
	}

	inline void SimpleScrollBarWidget::SetButtonMorePressed(bool pressed)
	{
		if (m_buttonMorePressed == pressed)
			return;

		m_buttonMorePressed = pressed;
		if (pressed)
			m_currentPressedButton = PressedButton_More;
		else if (m_currentPressedButton == PressedButton_More)
			m_currentPressedButton = PressedButton_None;

		OnButtonMorePress(m_buttonMorePressed);
	}

	inline void SimpleScrollBarWidget::SetButtonLessPressed(bool pressed)
	{
		if (m_buttonLessPressed == pressed)
			return;

		m_buttonLessPressed = pressed;
		if (pressed)
			m_currentPressedButton = PressedButton_Less;
		else if (m_currentPressedButton == PressedButton_Less)
			m_currentPressedButton = PressedButton_None;

		OnButtonMorePress(m_buttonLessPressed);
	}

	inline void SimpleScrollBarWidget::SetBackgroundPressed(bool pressed)
	{
		if (m_backgroundPressed == pressed)
			return;

		m_backgroundPressed = pressed;
		if (pressed)
			m_currentPressedButton = PressedButton_Background;
		else if (m_currentPressedButton == PressedButton_Background)
			m_currentPressedButton = PressedButton_None;

		OnBackgroundPress(pressed);
	}

	inline void SimpleScrollBarWidget::SetHovered(bool hovered)
	{
		if (m_hovered == hovered)
			return;

		m_hovered = hovered;

		OnHover(m_hovered);
	}

	inline void SimpleScrollBarWidget::SetButtonMoreHovered(bool hovered)
	{
		if (m_buttonMoreHovered == hovered)
			return;

		m_buttonMoreHovered = hovered;

		OnButtonMoreHover(m_buttonMoreHovered);
	}

	inline void SimpleScrollBarWidget::SetButtonLessHovered(bool hovered)
	{
		if (m_buttonLessHovered == hovered)
			return;

		m_buttonLessHovered = hovered;

		OnButtonLessHover(m_buttonLessHovered);
	}
}
