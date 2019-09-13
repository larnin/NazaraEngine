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
}
