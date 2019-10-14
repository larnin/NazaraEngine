#include <NDK/Widgets/Base/BaseSliderWidget.hpp>

namespace Ndk
{
	BaseSliderWidget::BaseSliderWidget(BaseWidget* parent):
	BaseWidget(parent),
	m_min{0},
	m_max{100},
	m_step{0},
	m_value{0},
	m_valueSize{0},
	m_orientation{SliderOrientation_Horizontal}
	{

	}
}
