
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

	inline SliderOrientation SliderWidget::GetOrientation() const
	{
		return m_orientation;
	}

	void SliderWidget::SetRange(float min, float max)
	{
		m_minValue = min;
		m_maxValue = max;
		Layout();
	}

	void SliderWidget::SetMinValue(float min)
	{
		m_minValue = min;
		Layout();
	}

	void SliderWidget::SetMaxValue(float max)
	{
		m_maxValue = max;
		Layout();
	}

	void SliderWidget::SetStep(float step)
	{
		m_step = step;
		Layout();
	}

	void SliderWidget::SetValue(float value)
	{
		value = std::max(value, m_minValue);
		value = std::min(value, m_maxValue);

		m_value = value;
		UpdateText();
		Layout();
	}

	void SliderWidget::ShowValue(bool show)
	{
		m_showValue = show;
		UpdateSize();
	}

	void SliderWidget::SetOrientation(SliderOrientation orientation)
	{
		m_orientation = orientation;
		UpdateSize();
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
		return { s_textSize , s_textSize / 2.0f };
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
