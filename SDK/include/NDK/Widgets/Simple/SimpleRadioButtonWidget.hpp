#pragma once

#ifndef NDK_WIDGETS_SIMPLERADIOBUTTONWIDGET_HPP
#define NDK_WIDGETS_SIMPLERADIOBUTTONWIDGET_HPP

#include <Ndk/Widgets/Base/TexturedButtonWidget.hpp>

namespace Ndk
{
	class NDK_API SimpleRadioButtonWidget : public TexturedButtonWidget
	{
		friend class Sdk;

	public:
		SimpleRadioButtonWidget(BaseWidget* parent);
		SimpleRadioButtonWidget(const SimpleRadioButtonWidget&) = delete;
		SimpleRadioButtonWidget(SimpleRadioButtonWidget&&) = default;
		virtual ~SimpleRadioButtonWidget() = default;

		int GetRenderOrderIndex() const override;
		inline Nz::TextureRef GetCheckTexture(bool checked) const;
		inline Nz::Rectf GetCheckTextureCoord(bool checked) const;
		inline Nz::Color GetCheckTextureColor(bool checked) const;

		inline void SetCheckTexture(Nz::TextureRef texture, bool checked);
		inline void SetCheckTextureCoord(const Nz::Rectf & coord, bool checked);
		inline void SetCheckTextureRect(const Nz::Rectui & rect, bool checked);
		inline void SetCheckButtonColor(const Nz::Color & color, bool checked);

	protected:
		virtual void Layout() override;

	private:
		EntityHandle m_checkEntity;
		Nz::SpriteRef m_checkSprite;

		ButtonInfo m_checkedData;
		ButtonInfo m_uncheckedData;

		static bool Initialize();
		static void Uninitialize();

		static const std::string s_buttonIdleName;
		static const std::string s_buttonHoveredName;
		static const std::string s_buttonDisabledName;
		static const std::string s_checkmarkName;
	};
}

#include "NDK/Widgets/Simple/SimpleRadioButtonWidget.inl"

#endif
