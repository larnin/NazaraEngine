
#include <NDK/Widgets/Simple/SimpleCheckboxWidget.hpp>

namespace Ndk
{
	inline Nz::TextureRef SimpleCheckboxWidget::GetCheckTexture(CheckboxState state) const
	{
		NazaraAssert(state <= CheckboxState_Max, "You can't get any texture on this CheckboxState");
		return m_checkDatas[state].texture;
	}

	inline Nz::Rectf SimpleCheckboxWidget::GetCheckTextureCoord(CheckboxState state) const
	{
		NazaraAssert(state <= CheckboxState_Max, "You can't get any texture coords on this CheckboxState");
		return m_checkDatas[state].textureCoords;
	}

	inline Nz::Color SimpleCheckboxWidget::GetCheckTextureColor(CheckboxState state) const
	{
		NazaraAssert(state <= CheckboxState_Max, "You can't get any texture coords on this CheckboxState");
		return m_checkDatas[state].color;
	}

	inline void SimpleCheckboxWidget::SetCheckTexture(Nz::TextureRef texture, CheckboxState state)
	{
		if (state == CheckboxState_All)
		{
			for (unsigned int i = 0; i <= CheckboxState_Max; i++)
				m_checkDatas[i].texture = texture;
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture on this ButtonState");

		m_checkDatas[state].texture = texture;

		Layout();
	}

	inline void SimpleCheckboxWidget::SetCheckTextureCoord(const Nz::Rectf & coord, CheckboxState state)
	{
		if (state == CheckboxState_All)
		{
			for (unsigned int i = 0; i <= CheckboxState_Max; i++)
				m_checkDatas[i].textureCoords = coord;
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture on this ButtonState");

		m_checkDatas[state].textureCoords = coord;

		Layout();
	}

	inline void SimpleCheckboxWidget::SetCheckTextureRect(const Nz::Rectui & rect, CheckboxState state)
	{
		if (state == CheckboxState_All)
		{
			for (unsigned int i = 0; i <= CheckboxState_Max; i++)
			{
				NazaraAssert(m_checkDatas[i].texture, "No texture defined on this ButtonState");

				Nz::Vector3ui texSize = m_checkDatas[i].texture->GetSize();

				m_checkDatas[i].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
					static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);
			}

			Layout();
			return;
		}

		NazaraAssert(state <= CheckboxState_Max, "You can't set any texture coords on this ButtonState");

		NazaraAssert(m_checkDatas[state].texture, "No texture defined on this ButtonState");

		Nz::Vector3ui texSize = m_checkDatas[state].texture->GetSize();

		m_checkDatas[state].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);

		Layout();
	}

	inline void SimpleCheckboxWidget::SetCheckButtonColor(const Nz::Color & color, CheckboxState state)
	{
		if (state == CheckboxState_All)
		{
			for (unsigned int i = 0; i <= CheckboxState_Max; i++)
				m_checkDatas[i].color = color;
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture on this ButtonState");

		m_checkDatas[state].color = color;

		Layout();
	}
}
