#include <NDK/Widgets/Simple/SimpleScrollAreaWidget.hpp>
#include <NDK/Widgets/Base/BaseSliderWidget.hpp>

namespace Ndk
{
	template<typename T, typename... Args>
	T* SimpleScrollAreaWidget::CreateAreaWidget(Args&&... args)
	{
		if (m_areaWidget != nullptr)
			m_areaWidget->Destroy();

		T* widget = m_parentAreaWidget->Add<T>(std::forward<Args>(args)...);
		m_areaWidget = widget;

		return widget;
	}

	inline BaseWidget* SimpleScrollAreaWidget::GetAreaWidget()
	{
		return m_areaWidget;
	}

	inline void SimpleScrollAreaWidget::DisableHorizontalScrollBar()
	{
		EnableHorizontalScrollBar(false);
	}

	inline void SimpleScrollAreaWidget::DisableVerticalScrollBar()
	{
		EnableVerticalScrollBar(false);
	}

	template<typename T, typename... Args>
	T* SimpleScrollAreaWidget::CreateHorizontalScrollBar(Args&&... args)
	{
		if (m_horizontalSlider != nullptr)
			m_horizontalSlider->Destroy();

		T* scrollBar = Add<T>(std::forward<Args>(args)...);
		m_horizontalSlider = scrollBar;
		m_horizontalSlider->SetOrientation(SliderOrientation_Horizontal);

		scrollBar->OnValueChange.Connect([this](float value) {OnHorizontalScrollValueChange(value); });

		ResizeArea();

		return scrollBar;
	}

	template<typename T, typename... Args>
	T* SimpleScrollAreaWidget::CreateVerticalScrollBar(Args&&... args)
	{
		if (m_verticalSlider != nullptr)
			m_verticalSlider->Destroy();

		T* scrollBar = Add<T>(std::forward<Args>(args)...);
		m_verticalSlider = scrollBar;
		m_verticalSlider->SetOrientation(SliderOrientation_Vertical);

		scrollBar->OnValueChange.Connect([this](float value) {OnHorizontalScrollValueChange(value); });

		ResizeArea();

		return scrollBar;
	}

	inline BaseSliderWidget* SimpleScrollAreaWidget::GetHorizontalScrollBar() const
	{
		return m_horizontalSlider;
	}

	inline BaseSliderWidget* SimpleScrollAreaWidget::GetVerticalScrollBar() const
	{
		return m_verticalSlider;
	}

	inline bool SimpleScrollAreaWidget::IsHorizontalScrollBarEnabled() const
	{
		return m_horizontalSlider != nullptr;
	}

	inline bool SimpleScrollAreaWidget::IsVerticalScrollBarEnabled() const
	{
		return m_verticalSlider != nullptr;
	}

	inline void SimpleScrollAreaWidget::SetScrollBarMargin(float margin)
	{
		m_barMargin = margin;

		ResizeArea();
	}

	inline float SimpleScrollAreaWidget::GetScrollBarMargin() const
	{
		return m_barMargin;
	}

	inline void SimpleScrollAreaWidget::SetAreaOffset(Nz::Vector2f offset)
	{
		m_offset = offset;

		Layout();
	}

	inline void SimpleScrollAreaWidget::SetAreaOffset(float offsetX, float offsetY)
	{
		SetAreaOffset(Nz::Vector2f(offsetX, offsetY));
	}

	inline Nz::Vector2f SimpleScrollAreaWidget::GetAreaOffset() const
	{
		return m_offset;
	}
}
