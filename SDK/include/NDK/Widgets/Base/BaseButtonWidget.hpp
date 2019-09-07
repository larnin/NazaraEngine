
#pragma once

#ifndef NDK_WIDGETS_BASEBUTTONWIDGET_HPP
#define NDK_WIDGETS_BASEBUTTONWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Widgets/Enums.hpp>
#include <vector>

namespace Ndk
{
	class NDK_API BaseButtonWidget : public BaseWidget
	{
		public:
			BaseButtonWidget(const BaseButtonWidget&) = delete;
			BaseButtonWidget(BaseButtonWidget&&) = default;
			virtual ~BaseButtonWidget() = default;

			inline void CheckNextState();
			inline void EnableTristate(bool enabled);

			inline bool IsCheckable() const;
			inline bool IsChecked() const;
			inline bool IsPressed() const;
			inline bool IsTristateEnabled() const;
			inline bool IsRadioButton() const;

			inline CheckboxState GetCheckState() const;

			inline void SetCheckable(bool checkable);
			inline void SetChecked(bool checked);
			inline void SetCheckState(CheckboxState state);
			inline void EnableRadioButton(bool enabled);

			NazaraSignal(OnPress);
			NazaraSignal(OnRelease);
			NazaraSignal(OnToggle, bool /*Toggled*/);
			NazaraSignal(OnCheckStateChange, CheckboxState /*state*/);

		protected:
			BaseButtonWidget(BaseWidget* parent);

			inline void SetPressed(bool pressed, bool toggle = true);

		private:
			bool m_checkable;
			CheckboxState m_checkState;
			bool m_tristateEnabled;
			bool m_pressed;
			bool m_radioButton;
	};

}

#include <NDK/Widgets/Base/BaseButtonWidget.inl>

#endif // NDK_WIDGETS_BUTTONWIDGET_HPP
