
#include <NDK/Widgets/Simple/SimpleRadioButtonWidget.hpp>

namespace Ndk
{
	inline Nz::TextureRef SimpleRadioButtonWidget::GetCheckTexture(bool checked) const
	{
		if (checked)
			return m_checkedData.texture;
		else return m_uncheckedData.texture;
	}

	inline Nz::Rectf SimpleRadioButtonWidget::GetCheckTextureCoord(bool checked) const
	{
		if(checked)
			return m_checkedData.textureCoords;
		else return m_uncheckedData.textureCoords;
	}

	inline Nz::Color SimpleRadioButtonWidget::GetCheckTextureColor(bool checked) const
	{
		if (checked)
			return m_checkedData.color;
		else return m_uncheckedData.color;
	}

	inline void SimpleRadioButtonWidget::SetCheckTexture(Nz::TextureRef texture, bool checked)
	{
		if (checked)
			m_checkedData.texture = texture;
		else m_uncheckedData.texture = texture;

		Layout();
	}

	inline void SimpleRadioButtonWidget::SetCheckTextureCoord(const Nz::Rectf & coord, bool checked)
	{
		if (checked)
			m_checkedData.textureCoords = coord;
		else m_uncheckedData.textureCoords = coord;
	
		Layout();
	}

	inline void SimpleRadioButtonWidget::SetCheckTextureRect(const Nz::Rectui & rect, bool checked)
	{
		ButtonInfo & infos = checked ? m_checkedData : m_uncheckedData;

		NazaraAssert(infos.texture, "No texture defined on this check state");

		Nz::Vector3ui texSize = infos.texture->GetSize();

		infos.textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);

		Layout();
	}

	inline void SimpleRadioButtonWidget::SetCheckButtonColor(const Nz::Color & color, bool checked)
	{
		if (checked)
			m_checkedData.color = color;
		else m_uncheckedData.color = color;

		Layout();
	}
}
