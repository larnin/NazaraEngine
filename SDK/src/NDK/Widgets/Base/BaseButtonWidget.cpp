
#include <NDK/Widgets/Base/BaseButtonWidget.hpp>

namespace Ndk
{
	BaseButtonWidget::BaseButtonWidget(BaseWidget* parent) :
	BaseWidget(parent),
	m_checkable{false},
	m_checkState{ CheckboxState_Unchecked },
	m_tristateEnabled{false},
	m_pressed{false}
	{

	}
}
