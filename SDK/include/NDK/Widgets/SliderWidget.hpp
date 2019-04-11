#pragma once

#ifndef NDK_WIDGETS_SLIDERWIDGET_HPP
#define NDK_WIDGETS_SLIDERWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Widgets/Enums.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <Nazara/Renderer/Texture.hpp>
#include <Nazara/Graphics/Sprite.hpp>
#include <Nazara/Graphics/TextSprite.hpp>

namespace Ndk
{
	class NDK_API SliderWidget : public BaseWidget
	{
	public:
		SliderWidget(BaseWidget* parent);
		SliderWidget(const SliderWidget&) = delete;
		SliderWidget(SliderWidget&&) = default;
		~SliderWidget() = default;

		//virtual CheckboxWidget* Clone() const = 0;

		inline float GetMinValue() const;
		inline float GetMaxValue() const;
		inline float GetStep() const;
		inline float GetValue() const;
		inline bool IsValueShowed() const;
		inline SliderOrientation GetOrientation() const;

		inline void SetRange(float min, float max);
		inline void SetMinValue(float min);
		inline void SetMaxValue(float max);
		inline void SetStep(float step);
		inline void SetValue(float value);
		inline void ShowValue(bool show);
		inline void SetOrientation(SliderOrientation orientation);

		inline Nz::Vector2f GetCursorSize() const;
		inline Nz::Vector2f GetTextSize() const;
		inline Nz::Vector2f GetLineSize() const;
		inline Nz::Vector2f GetTextSpriteSize() const;

		SliderWidget& operator=(const SliderWidget&) = delete;
		SliderWidget& operator=(SliderWidget&&) = default;

		NazaraSignal(OnStateChanged, const SliderWidget* /*slider*/);

	private:
		void Layout() override;
		void UpdateSize();
		void UpdateText();

		void OnMouseMoved(int x, int y, int deltaX, int deltaY) override;
		void OnMouseButtonPress(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseEnter() override;
		void OnMouseExit() override;

		EntityHandle m_lineEntity;
		EntityHandle m_cursorEntity;
		EntityHandle m_textEntity;

		Nz::SpriteRef m_lineSprite;
		Nz::SpriteRef m_cursorSprite;
		Nz::TextSpriteRef m_textSprite;

		static Nz::Color s_lineColor;
		static Nz::Color s_cursorColor;
		static Nz::Color s_cursorHoverColor;
		static Nz::Color s_cursorPressColor;
		static float s_cursorRatio;
		static float s_lineRatio;
		static float s_textSize;
		static unsigned int s_precision;

		float m_minValue;
		float m_maxValue;
		float m_step;
		float m_value;
		SliderOrientation m_orientation;
		float m_textWidth;
		bool m_mousePressed;
		bool m_showValue;
	};
}

#include <NDK/Widgets/SliderWidget.inl>

#endif //NDK_WIDGETS_SLIDERWIDGET_HPP
