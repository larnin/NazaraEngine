
namespace Ndk
{
	void RadioButtonWidget::EnableRadioButton(bool enable)
	{
		m_radioButtonEnabled = enable;
		UpdateRadioButton();
	}

	bool RadioButtonWidget::IsRadioButtonEnabled()
	{
		return m_radioButtonEnabled;
	}

	const Nz::Vector2f& RadioButtonWidget::GetRadioButtonSize() const
	{
		return m_radioButtonBackgroundSprite->GetSize();
	}

	bool RadioButtonWidget::GetState() const
	{
		return m_state;
	}

	float RadioButtonWidget::GetTextMargin() const
	{
		return m_textMargin;
	}

	void RadioButtonWidget::SetRadioButtonSize(const Nz::Vector2f& size)
	{
		m_radioButtonBackgroundSprite->SetSize(size);
		m_radioButtonContentSprite->SetSize(size);

		UpdateSize();
		Layout();
	}

	void RadioButtonWidget::SetTextMargin(float margin)
	{
		m_textMargin = margin;
		Layout();
	}

	void RadioButtonWidget::UpdateText(const Nz::AbstractTextDrawer& drawer)
	{
		m_textSprite->Update(drawer);

		UpdateSize();
		Layout();
	}

	bool RadioButtonWidget::ContainsRadioButton(int x, int y) const
	{
		Nz::Vector2f radioButtonSize = GetRadioButtonSize();
		Nz::Vector3f pos = m_radioButtonBackgroundEntity->GetComponent<NodeComponent>().GetPosition(Nz::CoordSys_Local);

		return x > pos.x && x < pos.x + radioButtonSize.x &&
			y > pos.y && y < pos.y + radioButtonSize.y;
	}
}
