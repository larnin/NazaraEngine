
#include <NDK/Widgets/ScrollAreaWidget.hpp>

namespace Ndk
{
	ScrollAreaWidget::ScrollAreaWidget(BaseWidget* parent) :
	BaseWidget{ parent },
	m_verticalBar{ nullptr },
	m_horizontalBar{ nullptr },
	m_areaWidget{ nullptr },
	m_offset{ 0, 0 }
	{
		m_parentAreaWidget = Add<BaseWidget>();
		m_parentAreaWidget->SetPosition(0, 0);

		EnableVerticalScrollBar(true);

		SetPreferredSize(Nz::Vector2f(100, 100));
	}

	void ScrollAreaWidget::OnLayout()
	{
		BaseWidget::OnLayout();

		if (m_areaWidget == nullptr)
		{
			if (m_horizontalBar != nullptr)
			{
				m_horizontalBar->SetMaxValue(1);
				m_horizontalBar->SetValueSize(1);
			}
			if (m_verticalBar != nullptr)
			{
				m_verticalBar->SetMaxValue(1);
				m_verticalBar->SetValueSize(1);
			}
			return;
		}

		Nz::Vector2f size = GetSize();

		Nz::Vector2f areaSize = size;

		if (m_verticalBar != nullptr)
			areaSize.x -= m_verticalBar->GetWidth();

		if (m_horizontalBar != nullptr)
			areaSize.y -= m_horizontalBar->GetHeight();

		m_parentAreaWidget->Resize(areaSize);

		Nz::Vector2f areaPreferedSize = m_areaWidget->GetPreferredSize();
		if (areaPreferedSize.x < areaSize.x)
			areaPreferedSize.x = areaSize.x;
		if (areaPreferedSize.y < areaSize.y)
			areaPreferedSize.y = areaSize.y;

		if (m_horizontalBar != nullptr)
		{
			m_horizontalBar->SetMaxValue(areaPreferedSize.x);
			m_horizontalBar->SetValueSize(areaSize.x);

			Nz::Vector2f barSize = m_horizontalBar->GetSize();
			m_horizontalBar->Resize(Nz::Vector2f(areaSize.x, barSize.y));
			m_horizontalBar->SetPosition(0, areaSize.y);
		}

		if (m_verticalBar != nullptr)
		{
			m_verticalBar->SetMaxValue(areaPreferedSize.y);
			m_verticalBar->SetValueSize(areaSize.y);

			Nz::Vector2f barSize = m_verticalBar->GetSize();
			m_verticalBar->Resize(Nz::Vector2f(barSize.x, areaSize.y));
			m_verticalBar->SetPosition(areaSize.x, 0);
		}

		m_areaWidget->Resize(areaPreferedSize);
		m_areaWidget->SetPosition(-m_offset);
	}

	void ScrollAreaWidget::EnableVerticalScrollBar(bool enabled)
	{
		if (enabled)
		{
			if (m_verticalBar != nullptr)
				return;
			m_verticalBar = Add<ScrollBarWidget>();
			m_verticalBar->SetOrientation(ScrollBarOrientation::ScrollBarOrientation_Vertical);
			m_verticalBar->SetMinValue(0);

			m_verticalBar->OnValueChanged.Connect([this](const Ndk::ScrollBarWidget * bar) { OnVerticalBarMoved(bar->GetValue()); });
		}
		else
		{
			if (m_verticalBar == nullptr)
				return;
			m_verticalBar->Destroy();
			m_verticalBar = nullptr;
		}
		m_offset.x = 0;

		Layout();
	}

	void ScrollAreaWidget::EnableHorizontalScrollBar(bool enabled)
	{
		if (enabled)
		{
			if (m_horizontalBar != nullptr)
				return;
			m_horizontalBar = Add<ScrollBarWidget>();
			m_horizontalBar->SetOrientation(ScrollBarOrientation::ScrollBarOrientation_Horizontal);
			m_horizontalBar->SetMinValue(0);

			m_horizontalBar->OnValueChanged.Connect([this](const Ndk::ScrollBarWidget * bar) { OnHorizontalBarMoved(bar->GetValue()); });
		}
		else
		{
			if (m_horizontalBar == nullptr)
				return;
			m_horizontalBar->Destroy();
			m_horizontalBar = nullptr;
		}
		m_offset.y = 0;

		Layout();
	}
}
