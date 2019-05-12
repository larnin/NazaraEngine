
namespace Ndk
{
	bool FoldableWidget::IsFolded() const
	{
		return m_folded;
	}

	void FoldableWidget::UpdateText(const Nz::AbstractTextDrawer& drawer)
	{
		m_textSprite->Update(drawer);

		//update prefered size
		SetFolded(m_folded);

		Layout();
	}

	template<typename T, typename... Args>
	T* FoldableWidget::CreateAreaWidget(Args&&... args)
	{
		if (m_areaWidget != nullptr)
			m_areaWidget->Destroy();

		T* widget = Add<T>(std::forward<Args>(args)...);
		m_areaWidget = widget;

		SetFolded(m_folded);

		return widget;
	}

	inline BaseWidget* FoldableWidget::GetAreaWidget()
	{
		return m_areaWidget;
	}
}
