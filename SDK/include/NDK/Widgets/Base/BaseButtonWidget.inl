
#include <NDK/Widgets/Base/BaseButtonWidget.hpp>

namespace Ndk
{
	inline bool BaseButtonWidget::IsCheckable() const
	{
		return m_checkable;
	}

	inline bool BaseButtonWidget::IsChecked() const
	{
		return m_checkState == CheckboxState_Checked;
	}

	inline bool BaseButtonWidget::IsPressed() const
	{
		return m_pressed;
	}

	inline bool BaseButtonWidget::IsTristateEnabled() const
	{
		return m_tristateEnabled;
	}


	inline bool BaseButtonWidget::IsRadioButton() const
	{
		return m_radioButton;
	}

	inline CheckboxState BaseButtonWidget::GetCheckState() const
	{
		return m_checkState;
	}

	inline void BaseButtonWidget::SetCheckable(bool checkable)
	{
		m_checkable = checkable;

		if (m_checkState != CheckboxState_Unchecked)
			SetChecked(false);

	}

	inline void BaseButtonWidget::SetChecked(bool checked)
	{
		if (checked)
			SetCheckState(CheckboxState_Checked);
		else SetCheckState(CheckboxState_Unchecked);
	}

	inline void BaseButtonWidget::SetCheckState(CheckboxState state)
	{
		if (!m_checkable)
			return;

		bool wasChecked = IsChecked();
		CheckboxState oldState = m_checkState;

		m_checkState = state;

		if(oldState == m_checkState)
			return;

		Layout();

		bool checked = IsChecked();

		if (wasChecked != checked)
			OnToggle(checked);
		OnCheckStateChange(m_checkState);

		if (checked && m_radioButton)
		{
			auto parent = GetParent();
			if (parent == nullptr)
				return;

			for (auto & child : parent->GetChilds())
			{
				if (child == this)
					continue;

				//not that good but there are no easy clean solution for this particular case
				auto button = dynamic_cast<BaseButtonWidget*>(child);
				if (button == nullptr)
					continue;

				if (!button->IsRadioButton())
					continue;
				button->SetChecked(false);
			}
		}
	}

	inline void  BaseButtonWidget::EnableRadioButton(bool enabled)
	{
		if (!enabled && m_radioButton)
			SetCheckable(false);

		m_radioButton = enabled;
		if (m_radioButton)
		{
			SetChecked(false);
			SetCheckable(true);
		}

		Layout();
	}

	inline void BaseButtonWidget::CheckNextState()
	{
		if (m_radioButton && m_checkState != CheckboxState_Unchecked)
			return;

		switch (m_checkState)
		{
		case CheckboxState_Unchecked:
			SetCheckState(CheckboxState_Checked);
			break;

		case CheckboxState_Checked:
			SetCheckState(m_tristateEnabled ? CheckboxState_Tristate : CheckboxState_Unchecked);
			break;

		case CheckboxState_Tristate:
			SetCheckState(CheckboxState_Unchecked);
			break;
		}
	}

	inline void BaseButtonWidget::EnableTristate(bool enabled)
	{
		m_tristateEnabled = enabled;

		if (!m_tristateEnabled && m_checkState == CheckboxState_Tristate)
			SetCheckState(CheckboxState_Unchecked);
	}

	inline void BaseButtonWidget::SetPressed(bool pressed, bool toggle)
	{
		m_pressed = pressed;

		Layout();

		if (m_checkable && toggle)
			CheckNextState();

		if (m_pressed)
			OnPress();
		else OnRelease();
	}
}
