
namespace Ndk
{
	template<typename T, typename... Args>
	T* ScrollAreaWidget::CreateAreaWidget(Args&&... args)
	{
		if (m_areaWidget != nullptr)
			m_areaWidget->Destroy();

		T* widget = m_parentAreaWidget->Add<T>(std::forward<Args>(args)...);
		m_areaWidget = widget;

		return widget;
	}

	BaseWidget* ScrollAreaWidget::GetAreaWidget()
	{
		return m_areaWidget;
	}

	bool ScrollAreaWidget::IsVerticalScrollBarEnabled() const
	{
		return m_verticalBar != nullptr;
	}

	bool ScrollAreaWidget::IsHorizontalScrollBarEnabled() const
	{
		return m_horizontalBar != nullptr;
	}

	void ScrollAreaWidget::OnHorizontalBarMoved(float value)
	{
		m_offset.x = value;
		m_areaWidget->SetPosition(-m_offset);
	}

	void ScrollAreaWidget::OnVerticalBarMoved(float value)
	{
		m_offset.y = value;
		m_areaWidget->SetPosition(-m_offset);
	}
}
