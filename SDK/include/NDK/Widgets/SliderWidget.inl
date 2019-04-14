
namespace Ndk
{
	float SliderWidget::GetMinValue() const
	{
		return m_minValue;
	}

	float SliderWidget::GetMaxValue() const
	{
		return m_maxValue;
	}

	float SliderWidget::GetStep() const
	{
		return m_step;
	}

	float SliderWidget::GetValue() const
	{
		return m_value;
	}

	bool SliderWidget::IsValueShowed() const
	{
		return m_showValue;
	}

	SliderOrientation SliderWidget::GetOrientation() const
	{
		return m_orientation;
	}

	unsigned int SliderWidget::GetPrecision() const
	{
		return m_precision;
	}

	unsigned int SliderWidget::GetCharacterSize() const
	{
		return m_characterSize;
	}

	void SliderWidget::SetRange(float min, float max)
	{
		m_minValue = min;
		m_maxValue = max;

		CheckValueBounds();

		Layout();
	}

	void SliderWidget::SetMinValue(float min)
	{
		m_minValue = min;

		CheckValueBounds();

		Layout();
	}

	void SliderWidget::SetMaxValue(float max)
	{
		m_maxValue = max;

		CheckValueBounds();

		Layout();
	}

	void SliderWidget::SetStep(float step)
	{
		m_step = step;
		Layout();
	}

	void SliderWidget::SetValue(float value)
	{
		m_value = value;

		CheckValueBounds();

		OnValueChanged(this);

		UpdateText();
		Layout();
	}

	void SliderWidget::ShowValue(bool show)
	{
		m_showValue = show;
		UpdateSize();
		Layout();
	}

	void SliderWidget::SetOrientation(SliderOrientation orientation)
	{
		m_orientation = orientation;
		UpdateSize();
		Layout();
	}

	void SliderWidget::SetPrecision(unsigned int precision)
	{
		if (precision < 0)
			precision = 0;
		m_precision = precision;
		UpdateText();
		UpdateSize();
		Layout();
	}

	void SliderWidget::SetCharacterSize(unsigned int characterSize)
	{
		m_characterSize = characterSize;
		UpdateText();
		UpdateSize();
		Layout();
	}

	void SliderWidget::CheckValueBounds()
	{
		float min = std::min(m_minValue, m_maxValue);
		float max = std::max(m_minValue, m_maxValue);
		if (m_value < min)
			SetValue(min);
		else if (m_value > max)
			SetValue(max);
	}

	Nz::Vector2f SliderWidget::GetCursorSize() const
	{
		Nz::Vector2f size = GetSize();
		size_t principalAxis = m_orientation == SliderOrientation::SliderOrientation_Horizontal ? 0 : 1;
		size_t otherAxis = m_orientation == SliderOrientation::SliderOrientation_Horizontal ? 1 : 0;
		size[principalAxis] = size[otherAxis] * s_cursorRatio;
		return size;
	}

	Nz::Vector2f SliderWidget::GetTextSize() const
	{
		if (!m_showValue)
			return { 0, 0 };

		unsigned int nbMinValueChar = static_cast<unsigned int>(std::log10(std::abs(m_minValue)));
		if (m_minValue < 0)
			nbMinValueChar++;
		unsigned int nbMaxValueChar = static_cast<unsigned int>(std::log10(std::abs(m_maxValue)));
		if (m_maxValue < 0)
			nbMaxValueChar++;
		unsigned int nbChar = std::max(nbMinValueChar, nbMaxValueChar);
		if (m_precision > 0)
			nbChar += m_precision + 1;

		return { (nbChar + 1) * s_charWidth * m_characterSize , s_textHeight * m_characterSize };
	}


	Nz::Vector2f SliderWidget::GetTextSpriteSize() const
	{
		if (!m_showValue)
			return { 0, 0 };
		return Nz::Vector2f(m_textSprite->GetBoundingVolume().obb.localBox.GetLengths());
	}

	Nz::Vector2f SliderWidget::GetLineSize() const
	{
		Nz::Vector2f size = GetSize();
		Nz::Vector2f textSize = GetTextSize();
		Nz::Vector2f cursorSize = GetCursorSize();

		size_t principalAxis = m_orientation == SliderOrientation::SliderOrientation_Horizontal ? 0 : 1;
		size_t otherAxis = m_orientation == SliderOrientation::SliderOrientation_Horizontal ? 1 : 0;

		size[principalAxis] -= cursorSize[principalAxis] + textSize[principalAxis];
		size[otherAxis] *= s_lineRatio;
		return size;
	}
}
