
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
		if (!m_checkable)
			return;

		CheckboxState oldState = m_checkState;

		if(checked)
			m_checkState = CheckboxState_Checked;
		else m_checkState = CheckboxState_Unchecked;

		if (oldState == m_checkState)
			return;

		Layout();

		OnToggle(m_checkState == CheckboxState_Checked);
		OnCheckStateChange(m_checkState);
	}

	inline void BaseButtonWidget::SetCheckState(CheckboxState state)
	{
		if (!m_checkable)
			return;

		bool wasChecked = IsChecked();
		CheckboxState oldState = m_checkState;

		m_checkState = state;

		if(oldState != m_checkState)
			return;

		Layout();

		bool checked = IsChecked();

		if (wasChecked != checked)
			OnToggle(checked);
		OnCheckStateChange(m_checkState);
	}

	inline void BaseButtonWidget::CheckNextState()
	{
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
