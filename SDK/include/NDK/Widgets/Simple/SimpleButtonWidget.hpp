#pragma once

#ifndef NDK_WIDGETS_SIMPLEBUTTONWIDGET_HPP
#define NDK_WIDGETS_SIMPLEBUTTONWIDGET_HPP

#include <Ndk/Widgets/Base/TexturedButtonWidget.hpp>

namespace Ndk
{
	class NDK_API SimpleButtonWidget : public TexturedButtonWidget
	{
		friend class Sdk;

	public:
		SimpleButtonWidget(BaseWidget* parent);
		SimpleButtonWidget(const SimpleButtonWidget&) = delete;
		SimpleButtonWidget(SimpleButtonWidget&&) = default;
		virtual ~SimpleButtonWidget() = default;

	private:
		static bool Initialize();
		static void Uninitialize();

		static const std::string s_buttonIdleName;
		static const std::string s_buttonHoveredName;
		static const std::string s_buttonPressedName;
		static const std::string s_buttonPressedHoveredName;
		static const std::string s_buttonDisabledName;
		static const unsigned int s_sliceSize;

	};
}

#endif
