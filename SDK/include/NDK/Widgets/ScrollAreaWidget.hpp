#pragma once

#ifndef NDK_WIDGETS_SCROLLAREAWIDGET_HPP
#define NDK_WIDGETS_SCROLLAREAWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Widgets/ScrollBarWidget.hpp>

namespace Ndk
{
	class NDK_API ScrollAreaWidget : public BaseWidget
	{
	public:
		ScrollAreaWidget(BaseWidget* parent);
		ScrollAreaWidget(const ScrollAreaWidget&) = delete;
		ScrollAreaWidget(ScrollAreaWidget&&) = default;
		~ScrollAreaWidget() = default;

		void EnableVerticalScrollBar(bool enabled);
		void EnableHorizontalScrollBar(bool enabled);

		template<typename T, typename... Args>
		T* CreateAreaWidget(Args&&... args);
		inline BaseWidget* GetAreaWidget();

		inline bool IsVerticalScrollBarEnabled() const;
		inline bool IsHorizontalScrollBarEnabled() const;

		ScrollAreaWidget& operator=(const ScrollAreaWidget&) = delete;
		ScrollAreaWidget& operator=(ScrollAreaWidget&&) = default;

	private:
		void OnLayout() override;

		inline void OnHorizontalBarMoved(float value);
		inline void OnVerticalBarMoved(float value);

		BaseWidget* m_parentAreaWidget;
		BaseWidget* m_areaWidget;

		ScrollBarWidget* m_verticalBar;
		ScrollBarWidget* m_horizontalBar;

		Nz::Vector2f m_offset;
	};
}

#include <NDK/Widgets/ScrollAreaWidget.inl>

#endif //NDK_WIDGETS_SCROLLAREAWIDGET_HPP
