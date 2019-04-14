
namespace Ndk
{
	void ScrollBarWidget::SetRange(float minValue, float maxValue)
	{
		m_minValue = minValue;
		m_maxValue = maxValue;

		CheckValueBounds();

		Layout();
	}

	void ScrollBarWidget::SetMinValue(float minValue)
	{
		m_minValue = minValue;

		CheckValueBounds();

		Layout();
	}

	void ScrollBarWidget::SetMaxValue(float maxValue)
	{
		m_maxValue = maxValue;

		CheckValueBounds();

		Layout();
	}

	void ScrollBarWidget::SetValueSize(float valueSize)
	{
		if (valueSize < 0)
			valueSize = 0;

		m_valueSize = valueSize;

		CheckValueBounds();

		Layout();
	}

	void ScrollBarWidget::SetValue(float value)
	{
		m_value = value;

		CheckValueBounds();

		OnValueChanged(this);

		Layout();
	}

	void ScrollBarWidget::SetOrientation(ScrollBarOrientation orientation)
	{
		m_orientation = orientation;

		Nz::Vector2f size{ 32.f, 100.f };
		if (m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal)
			std::swap(size.x, size.y);
		SetPreferredSize(size);

		Layout();
	}

	float ScrollBarWidget::GetMinValue() const
	{
		return m_minValue;
	}

	float ScrollBarWidget::GetMaxValue() const
	{
		return m_maxValue;
	}

	float ScrollBarWidget::GetValueSize() const
	{
		return m_valueSize;
	}

	float ScrollBarWidget::GetValue() const
	{
		return m_value;
	}

	ScrollBarOrientation ScrollBarWidget::GetOrientation() const
	{
		return m_orientation;
	}

	void ScrollBarWidget::CheckValueBounds()
	{
		float min = std::min(m_minValue, m_maxValue);
		float max = std::max(m_minValue, m_maxValue);
		if (m_valueSize > max - min)
			m_valueSize = max - min;

		if (m_value < min)
			SetValue(min);
		else if (m_value > max - m_valueSize)
			SetValue(max - m_valueSize);
	}

	Nz::Vector2f ScrollBarWidget::GetButtonSize() const
	{
		Nz::Vector2f size = Nz::Vector2f(m_topButtonSprite->GetBoundingVolume().obb.localBox.GetLengths());
		if (m_orientation == ScrollBarOrientation::ScrollBarOrientation_Horizontal)
			std::swap(size.x, size.y);
		return size;
	}
}
