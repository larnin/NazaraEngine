#pragma once

#ifndef NDK_WIDGETS_SPINBOXWIDGET_HPP
#define NDK_WIDGETS_SPINBOXWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Widgets/TextAreaWidget.hpp>

namespace Ndk
{
	class NDK_API SpinBoxWidget : public BaseWidget
	{
		enum class HoveredButton
		{
			noButton,
			topButton,
			bottomButton,
		};

	public:
		SpinBoxWidget(BaseWidget* parent);
		SpinBoxWidget(const SpinBoxWidget&) = delete;
		SpinBoxWidget(SpinBoxWidget&&) = default;
		~SpinBoxWidget() = default;

		inline unsigned int GetCharacterSize() const;
		inline const Nz::Color& GetTextColor() const;
		inline float GetValue() const;
		inline float GetMinValue() const;
		inline float GetMaxValue() const;
		inline unsigned int GetPrecision() const;
		inline float GetStep() const;

		inline void SetCharacterSize(unsigned int characterSize);
		inline void SetTextColor(const Nz::Color& text);
		void SetValue(float value);
		inline void SetRange(float minValue, float maxValue);
		inline void SetMinValue(float minValue);
		inline void SetMaxValue(float maxValue);
		inline void SetPrecision(unsigned int precision);
		inline void SetStep(float step);

		SpinBoxWidget& operator=(const SpinBoxWidget&) = delete;
		SpinBoxWidget& operator=(SpinBoxWidget&&) = default;

		NazaraSignal(OnValueChanged, const SpinBoxWidget* /*spinBox*/);

	private:
		void OnLayout() override;

		void OnMouseMoved(int x, int y, int deltaX, int deltaY) override;
		void OnMouseButtonPress(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseExit() override;

		void OnTextChanged(const std::string & text);

		void CheckValueBounds();

		HoveredButton GetButton(const Nz::Vector2f & pos) const;

		TextAreaWidget * m_textArea;

		Ndk::EntityHandle m_topButtonEntity;
		Ndk::EntityHandle m_bottomButtonEntity;

		Nz::SpriteRef m_topButtonSprite;
		Nz::SpriteRef m_bottomButtonSprite;

		float m_value;
		float m_minValue;
		float m_maxValue;
		float m_step;
		unsigned int m_precision;

		HoveredButton m_pressedButton;

		bool m_blockTextChangeSignal;

		static Nz::Color s_buttonBaseColor;
		static Nz::Color s_buttonHoveredColor;
		static Nz::Color s_buttonPressedColor;
		static float s_buttonsSpacing;
	};
}

#include <NDK/Widgets/SpinBoxWidget.inl>

#endif //NDK_WIDGETS_SPINBOXWIDGET_HPP
