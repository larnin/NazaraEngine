#include <NDK/Widgets/Base/TexturedButtonWidget.hpp>

namespace Ndk
{
	inline void TexturedButtonWidget::SetSliceMargin(float size)
	{
		m_buttonSprite->SetSliceMargin(size);
	}

	inline void TexturedButtonWidget::SetSliceMargin(unsigned int size)
	{
		m_buttonSprite->SetSliceMargin(size);
	}

	inline void TexturedButtonWidget::SetSliceMargin(float top, float down, float left, float right)
	{
		m_buttonSprite->SetSliceMargin(top, down, left, right);
	}

	inline void TexturedButtonWidget::SetSliceMargin(unsigned int top, unsigned int down, unsigned int left, unsigned int right)
	{
		m_buttonSprite->SetSliceMargin(top, down, left, right);
	}

	inline bool TexturedButtonWidget::IsButtonHovered() const
	{
		return m_hovered;
	}

	inline Nz::TextureRef TexturedButtonWidget::GetTexture(ButtonState state) const
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any texture on this ButtonState");

		return m_buttonsDatas[state].texture;
	}

	inline Nz::Rectf TexturedButtonWidget::GetTextureCoord(ButtonState state) const
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any texture coords on this ButtonState");

		return m_buttonsDatas[state].textureCoords;
	}

	inline Nz::Color TexturedButtonWidget::GetTextureColor(ButtonState state) const
	{
		NazaraAssert(state <= ButtonState_Max, "You can't get any color on this ButtonState");

		return m_buttonsDatas[state].color;
	}

	inline bool TexturedButtonWidget::HasKeepTextureRatio() const
	{
		return m_keepTextureRatio;
	}

	inline void TexturedButtonWidget::SetTexture(Nz::TextureRef texture, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_buttonsDatas[i].texture = texture;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture on this ButtonState");

		m_buttonsDatas[state].texture = texture;

		Layout();
	}

	inline void TexturedButtonWidget::SetTextureCoord(const Nz::Rectf & coord, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_buttonsDatas[i].textureCoords = coord;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this ButtonState");

		m_buttonsDatas[state].textureCoords = coord;

		Layout();
	}

	inline void TexturedButtonWidget::SetTextureRect(const Nz::Rectui & rect, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
			{
				NazaraAssert(m_buttonsDatas[i].texture, "No texture defined on this ButtonState");

				Nz::Vector3ui texSize = m_buttonsDatas[i].texture->GetSize();

				m_buttonsDatas[i].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
					static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);
			}
				
			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this ButtonState");

		NazaraAssert(m_buttonsDatas[state].texture, "No texture defined on this ButtonState");

		Nz::Vector3ui texSize = m_buttonsDatas[state].texture->GetSize();

		m_buttonsDatas[state].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);

		Layout();
	}

	inline void TexturedButtonWidget::SetButtonColor(const Nz::Color & color, ButtonState state)
	{
		if (state == ButtonState::ButtonState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_buttonsDatas[i].color = color;

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this ButtonState");

		m_buttonsDatas[state].color = color;

		Layout();
	}

	inline void TexturedButtonWidget::UpdateText(const Nz::AbstractTextDrawer& drawer)
	{
		m_textSprite->Update(drawer);

		UpdateSize();
	}

	inline void TexturedButtonWidget::SetTextAlignment(ButtonTextAlignment alignment)
	{
		m_textAlignment = alignment;

		UpdateSize();
	}

	inline void TexturedButtonWidget::SetTextPosition(ButtonTextAlignment position)
	{
		m_textPosition = position;

		UpdateSize();
	}

	inline void TexturedButtonWidget::SetTextMargin(float margin)
	{
		m_textMargin = margin;

		UpdateSize();
	}

	inline void TexturedButtonWidget::SetKeepTextureRatio(bool keepRatio)
	{
		m_keepTextureRatio = keepRatio;

		UpdateSize();
	}

	inline ButtonTextAlignment TexturedButtonWidget::GetTextAlignment() const
	{
		return m_textAlignment;
	}

	inline ButtonTextAlignment TexturedButtonWidget::GetTextPosition() const
	{
		return m_textPosition;
	}

	inline float TexturedButtonWidget::GetTextMargin() const
	{
		return m_textMargin;
	}

	inline Nz::Vector2f TexturedButtonWidget::GetButtonSize() const
	{
		return m_buttonSprite->GetSize();
	}

	inline void TexturedButtonWidget::SetButtonSize(Nz::Vector2f size)
	{
		if (m_keepTextureRatio)
		{
			Nz::Vector2f oldSize = m_buttonSprite->GetSize();
			float ratio = oldSize.x / oldSize.y;
			float newRatio = size.x / size.y;
			if (newRatio < ratio)
				size.y = oldSize.y / oldSize.x * size.x;
			else size.x = oldSize.x / oldSize.y * size.y;
		}
		m_buttonSprite->SetSize(size);
	}
}
