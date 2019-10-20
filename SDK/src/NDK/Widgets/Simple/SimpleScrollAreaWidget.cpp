#include <NDK/Widgets/Simple/SimpleScrollAreaWidget.hpp>
#include <NDK/Widgets/Simple/SimpleScrollBarWidget.hpp>

namespace Ndk
{
	SimpleScrollAreaWidget::SimpleScrollAreaWidget(BaseWidget* parent) :
	BaseWidget(parent),
	m_horizontalSlider{ nullptr },
	m_verticalSlider{ nullptr },
	m_areaWidget{ nullptr },
	m_barMargin{5},
	m_offset{0, 0}
	{
		m_parentAreaWidget = Add<BaseWidget>();
		m_parentAreaWidget->SetPosition(0, 0);

		EnableVerticalScrollBar();

		SetPreferredSize(Nz::Vector2f(200.f, 200.f));
	}

	BaseSliderWidget* SimpleScrollAreaWidget::EnableHorizontalScrollBar(bool enabled)
	{
		if (IsHorizontalScrollBarEnabled() == enabled)
			return m_horizontalSlider;

		BaseSliderWidget* scrollBar = nullptr;

		if (enabled)
			scrollBar = CreateHorizontalScrollBar<SimpleScrollBarWidget>();
		else
		{
			if (m_horizontalSlider != nullptr)
			{
				m_horizontalSlider->Destroy();

				ResizeArea();
			}

			m_offset = Nz::Vector2f(0, 0);
		}

		return scrollBar;
	}

	BaseSliderWidget* SimpleScrollAreaWidget::EnableVerticalScrollBar(bool enabled)
	{
		if (IsVerticalScrollBarEnabled() == enabled)
			return m_verticalSlider;

		BaseSliderWidget* scrollBar = nullptr;

		if (enabled)
			scrollBar = CreateVerticalScrollBar<SimpleScrollBarWidget>();
		else if (m_verticalSlider != nullptr)
		{
			m_verticalSlider->Destroy();

			ResizeArea();
		}

		return scrollBar;
	}

	void SimpleScrollAreaWidget::Layout()
	{
		m_parentAreaWidget->SetPosition(0, 0);

		if (m_areaWidget != nullptr)
			m_areaWidget->SetPosition(-m_offset);

		Nz::Vector2f size = GetSize();

		if (m_horizontalSlider != nullptr)
		{
			Nz::Vector2f hSize = m_horizontalSlider->GetSize();
			m_horizontalSlider->SetPosition(0, size.y - hSize.y);
		}

		if (m_verticalSlider != nullptr)
		{
			Nz::Vector2f vSize = m_verticalSlider->GetSize();
			m_verticalSlider->SetPosition(size.x - vSize.x, 0);
		}
	}

	void SimpleScrollAreaWidget::Resize(const Nz::Vector2f& size)
	{
		Nz::Vector2f newSize = size;
		newSize.Maximize(GetMinimumSize());
		newSize.Minimize(GetMaximumSize());

		SetSize(newSize);

		Nz::Vector2f hSize(0, 0);
		Nz::Vector2f vSize(0, 0);

		if (m_horizontalSlider != nullptr)
		{
			hSize = m_horizontalSlider->GetPreferredSize();
			hSize.Maximize(m_horizontalSlider->GetMinimumSize());
			hSize.Minimize(m_horizontalSlider->GetMaximumSize());
		}

		if (m_verticalSlider != nullptr)
		{
			vSize = m_verticalSlider->GetPreferredSize();
			vSize.Maximize(m_verticalSlider->GetMinimumSize());
			vSize.Minimize(m_verticalSlider->GetMaximumSize());
		}

		if (m_horizontalSlider != nullptr)
		{
			hSize.x = newSize.x - vSize.y;
			BaseWidget::Resize(*m_horizontalSlider, hSize);
		}

		if (m_verticalSlider != nullptr)
		{
			vSize.y = newSize.y - hSize.y;
			BaseWidget::Resize(*m_verticalSlider, vSize);
		}

		ResizeArea();
	}

	void SimpleScrollAreaWidget::OnHorizontalScrollValueChange(float value)
	{
		m_offset.x = value;

		Layout();
	}

	void SimpleScrollAreaWidget::OnVerticalScrollValueChange(float value)
	{
		m_offset.y = value;

		Layout();
	}

	Nz::Rectf SimpleScrollAreaWidget::GetAreaRect() const
	{
		Nz::Vector2f size = GetSize();

		if (m_horizontalSlider != nullptr)
		{
			Nz::Vector2f hSize = m_horizontalSlider->GetSize();
			size.y -= hSize.y + m_barMargin;
		}
		if (m_verticalSlider != nullptr)
		{
			Nz::Vector2f vSize = m_verticalSlider->GetSize();
			size.x -= vSize.x + m_barMargin;
		}

		return Nz::Rectf(0, 0, size.x, size.y);
	}

	void SimpleScrollAreaWidget::ResizeArea()
	{
		Nz::Rectf rect = GetAreaRect();

		BaseWidget::Resize(*m_parentAreaWidget, Nz::Vector2f(rect.width, rect.height));

		if (m_areaWidget != nullptr)
		{
			Nz::Vector2f areaScale(Nz::Vector2f(m_areaWidget->GetScale(Nz::CoordSys_Local)));
			Nz::Vector2f areaPreferedSize = m_areaWidget->GetPreferredSize() * areaScale;
			if (areaPreferedSize.x < rect.width)
				areaPreferedSize.x = rect.width;
			if (areaPreferedSize.y < rect.height)
				areaPreferedSize.y = rect.height;

			if (m_horizontalSlider != nullptr)
			{
				m_horizontalSlider->SetMax(areaPreferedSize.x);
				m_horizontalSlider->SetValueSize(rect.width);
			}
			else areaPreferedSize.x = rect.width;

			if (m_verticalSlider != nullptr)
			{
				m_verticalSlider->SetMax(areaPreferedSize.y);
				m_verticalSlider->SetValueSize(rect.height);
			}
			else areaPreferedSize.y = rect.height;

			BaseWidget::Resize(*m_areaWidget, areaPreferedSize / areaScale);
		}
	}
}
