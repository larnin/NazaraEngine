#pragma once

#ifndef NDK_WIDGETS_SIMPLESCROLLAREAWIDGET_HPP
#define NDK_WIDGETS_SIMPLESCROLLAREAWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Widgets/Enums.hpp>

namespace Ndk
{
	class BaseSliderWidget;

	class SimpleScrollAreaWidget : public BaseWidget
	{
	public:
		SimpleScrollAreaWidget(BaseWidget* parent);
		SimpleScrollAreaWidget(const SimpleScrollAreaWidget&) = delete;
		SimpleScrollAreaWidget(SimpleScrollAreaWidget&&) = default;
		virtual ~SimpleScrollAreaWidget() = default;

		template<typename T, typename... Args>
		T* CreateAreaWidget(Args&&... args);
		inline BaseWidget* GetAreaWidget();

		BaseSliderWidget* EnableHorizontalScrollBar(bool enabled = true);
		BaseSliderWidget* EnableVerticalScrollBar(bool enabled = true);
		inline void DisableHorizontalScrollBar();
		inline void DisableVerticalScrollBar();

		template<typename T, typename... Args>
		T* CreateHorizontalScrollBar(Args&&... args);
		template<typename T, typename... Args>
		T* CreateVerticalScrollBar(Args&&... args);

		inline BaseSliderWidget* GetHorizontalScrollBar() const;
		inline BaseSliderWidget* GetVerticalScrollBar() const;

		inline bool IsHorizontalScrollBarEnabled() const;
		inline bool IsVerticalScrollBarEnabled() const;

		inline void SetScrollBarMargin(float margin);
		inline float GetScrollBarMargin() const;

		inline void SetAreaOffset(Nz::Vector2f offset);
		inline void SetAreaOffset(float offsetX, float offsetY);
		inline Nz::Vector2f GetAreaOffset() const;

	protected:
		virtual void Layout() override;
		virtual void Resize(const Nz::Vector2f& size) override;

	private:
		void OnHorizontalScrollValueChange(float value);
		void OnVerticalScrollValueChange(float value);
		Nz::Rectf GetAreaRect() const;
		void ResizeArea();

		BaseSliderWidget* m_horizontalSlider;
		BaseSliderWidget* m_verticalSlider;

		BaseWidget* m_parentAreaWidget;
		BaseWidget* m_areaWidget;

		float m_barMargin;

		Nz::Vector2f m_offset;

	};

}

#include <NDK/Widgets/Simple/SimpleScrollAreaWidget.inl>

#endif //NDK_WIDGETS_SIMPLESCROLLAREAWIDGET_HPP
