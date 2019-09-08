#pragma once

#ifndef NDK_WIDGETS_BASESLIDERWIDGET_HPP
#define NDK_WIDGETS_BASESLIDERWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Widgets/Enums.hpp>

namespace Ndk
{
	class NDK_API BaseSliderWidget : public BaseWidget
	{
	public:
		BaseSliderWidget(const BaseSliderWidget&) = delete;
		BaseSliderWidget(BaseSliderWidget&&) = default;
		virtual ~BaseSliderWidget() = default;

		inline void SetRange(float min, float max);
		inline void SetMin(float min);
		inline void SetMax(float max);
		inline void SetStep(float step = 0);
		inline void SetValue(float value, bool ignoreStep = false);
		inline void SetNormalizedValue(float value, bool ignoreStep = false);
		inline void SetOrientation(SliderOrientation orientation);

		inline float GetMin() const;
		inline float GetMax() const;
		inline float GetStep() const;
		inline float GetValue() const;
		inline float GetNormalizedValue() const;
		inline SliderOrientation GetOrientation() const;

	protected:
		BaseSliderWidget(BaseWidget* parent);

		virtual void UpdatePreferedSize() = 0;

	private:
		float m_min;
		float m_max;
		float m_step;
		float m_value;
		SliderOrientation m_orientation;
	};
}

#include <NDK/Widgets/Base/BaseSliderWidget.inl>

#endif
