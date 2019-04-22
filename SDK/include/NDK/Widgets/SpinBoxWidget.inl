#pragma once

namespace Ndk
{
	unsigned int SpinBoxWidget::GetCharacterSize() const
	{
		return m_textArea->GetCharacterSize();
	}

	const Nz::Color& SpinBoxWidget::GetTextColor() const
	{
		return m_textArea->GetTextColor();
	}

	float SpinBoxWidget::GetValue() const
	{
		return m_value;
	}

	float SpinBoxWidget::GetMinValue() const
	{
		return m_minValue;
	}

	float SpinBoxWidget::GetMaxValue() const
	{
		return m_maxValue;
	}

	unsigned int SpinBoxWidget::GetPrecision() const
	{
		return m_precision;
	}

	float SpinBoxWidget::GetStep() const
	{
		return m_step;
	}

	void SpinBoxWidget::SetCharacterSize(unsigned int characterSize)
	{
		m_textArea->SetCharacterSize(characterSize);
	}

	void SpinBoxWidget::SetTextColor(const Nz::Color& text)
	{
		m_textArea->SetTextColor(text);
	}

	void SpinBoxWidget::SetRange(float minValue, float maxValue)
	{
		m_minValue = std::min(minValue, maxValue);
		m_maxValue = std::max(minValue, maxValue);

		CheckValueBounds();
	}

	void SpinBoxWidget::SetMinValue(float minValue)
	{
		m_minValue = minValue;
		if (m_minValue > m_maxValue)
			std::swap(m_minValue, m_maxValue);

		CheckValueBounds();
	}

	void SpinBoxWidget::SetMaxValue(float maxValue)
	{
		m_maxValue = maxValue;
		if (m_minValue > m_maxValue)
			std::swap(m_minValue, m_maxValue);

		CheckValueBounds();
	}

	void SpinBoxWidget::SetPrecision(unsigned int precision)
	{
		m_precision = precision;

		OnLayout();
	}

	void SpinBoxWidget::SetStep(float step)
	{
		m_step = step;
	}
}
