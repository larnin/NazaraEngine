#pragma once

#ifndef NDK_WIDGETS_SIMPLECHECKBOXWIDGET_HPP
#define NDK_WIDGETS_SIMPLECHECKBOXWIDGET_HPP

#include <Ndk/Widgets/Base/TexturedButtonWidget.hpp>

namespace Ndk
{
	class NDK_API SimpleCheckboxWidget : public TexturedButtonWidget
	{
		friend class Sdk;

	public:
		SimpleCheckboxWidget(BaseWidget* parent);
		SimpleCheckboxWidget(const TexturedButtonWidget&) = delete;
		SimpleCheckboxWidget(SimpleCheckboxWidget&&) = default;
		virtual ~SimpleCheckboxWidget() = default;

		int GetRenderOrderIndex() const override;

		inline Nz::TextureRef GetCheckTexture(CheckboxState state) const;
		inline Nz::Rectf GetCheckTextureCoord(CheckboxState state) const;
		inline Nz::Color GetCheckTextureColor(CheckboxState state) const;

		inline void SetCheckTexture(Nz::TextureRef texture, CheckboxState state = CheckboxState_All);
		inline void SetCheckTextureCoord(const Nz::Rectf & coord, CheckboxState state = CheckboxState_All);
		inline void SetCheckTextureRect(const Nz::Rectui & rect, CheckboxState state = CheckboxState_All);
		inline void SetCheckButtonColor(const Nz::Color & color, CheckboxState state = CheckboxState_All);

	protected:
		virtual void Layout() override;

	private:
		EntityHandle m_checkEntity;
		Nz::SpriteRef m_checkSprite;

		std::array<ButtonInfo, CheckboxState_Max + 1> m_checkDatas;

		static bool Initialize();
		static void Uninitialize();

		static const std::string s_buttonIdleName;
		static const std::string s_buttonHoveredName;
		static const std::string s_buttonDisabledName;
		static const std::string s_checkmarkName;
		static const std::string s_ckeckTristateName;
	};
}

#include "NDK/Widgets/Simple/SimpleCheckboxWidget.inl"

#endif
