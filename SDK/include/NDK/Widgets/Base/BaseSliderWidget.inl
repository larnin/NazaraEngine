#include <NDK/Widgets/Base/BaseSliderWidget.hpp>

namespace Ndk
{
	inline void BaseSliderWidget::SetRange(float min, float max)
	{
		m_min = min;
		m_max = max;

		SetValue(m_value);
	}

	inline void BaseSliderWidget::SetMin(float min)
	{
		m_min = min;

		SetValue(m_value);
	}

	inline void BaseSliderWidget::SetMax(float max)
	{
		m_max = max;

		SetValue(m_value);
	}

	inline void BaseSliderWidget::SetStep(float step)
	{
		m_step = step;

		SetValue(m_value);
	}

	inline void BaseSliderWidget::SetValue(float value, bool ignoreStep)
	{
		value = std::max(value, m_min);
		value = std::min(value, m_max);

		if (!ignoreStep && m_step > 0)
		{
			value = std::round(value / m_step) * m_step;
		}

		m_value = value;

		OnValueChange(m_value);
		OnValueChangeNormalized((m_value - m_min) / (m_max - m_min));

		Layout();
	}

	inline void BaseSliderWidget::SetNormalizedValue(float value, bool ignoreStep)
	{
		SetValue(value * (m_max - m_min) + m_min, ignoreStep);
	}

	inline void BaseSliderWidget::SetOrientation(SliderOrientation orientation)
	{
		if (m_orientation == orientation)
			return;

		m_orientation = orientation;

		UpdatePreferedSize();
	}

	inline float BaseSliderWidget::GetMin() const
	{
		return m_min;
	}

	inline float BaseSliderWidget::GetMax() const
	{
		return m_max;
	}

	inline float BaseSliderWidget::GetStep() const
	{
		return m_step;
	}

	inline float BaseSliderWidget::GetValue() const
	{
		return m_value;
	}

	inline float BaseSliderWidget::GetNormalizedValue() const
	{
		return (m_value - m_min) / (m_max - m_min);
	}

	inline SliderOrientation BaseSliderWidget::GetOrientation() const
	{
		return m_orientation;
	}
}
