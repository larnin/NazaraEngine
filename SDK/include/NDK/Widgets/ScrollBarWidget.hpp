#pragma once

#ifndef NDK_WIDGETS_SCROLLBARWIDGET_HPP
#define NDK_WIDGETS_SCROLLBARWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <NDK/Widgets/Enums.hpp>
#include <Nazara/Graphics/Sprite.hpp>

#include <algorithm>

namespace Ndk
{
	class NDK_API ScrollBarWidget : public BaseWidget
	{
		friend class Sdk;

		enum class PressedButton
		{
			none,
			topButton,
			bottomButton,
			cursor,
		};

	public:
		ScrollBarWidget(BaseWidget* parent);
		ScrollBarWidget(const ScrollBarWidget&) = delete;
		ScrollBarWidget(ScrollBarWidget&&) = default;
		~ScrollBarWidget() = default;

		inline void SetRange(float minValue, float maxValue);
		inline void SetMinValue(float minValue);
		inline void SetMaxValue(float maxValue);
		inline void SetValueSize(float valueSize);
		inline void SetValue(float value);
		inline void SetOrientation(ScrollBarOrientation orientation);

		inline float GetMinValue() const;
		inline float GetMaxValue() const;
		inline float GetValueSize() const;
		inline float GetValue() const;
		inline ScrollBarOrientation GetOrientation() const;

		ScrollBarWidget& operator=(const ScrollBarWidget&) = delete;
		ScrollBarWidget& operator=(ScrollBarWidget&&) = default;

		NazaraSignal(OnValueChanged, const ScrollBarWidget* /*scrollBar*/);

	private:
		static bool Initialize();
		static void Uninitialize();

		inline void CheckValueBounds();

		void OnLayout() override;
		void UpdateRotation();

		inline Nz::Vector2f GetButtonSize() const;

		PressedButton GetButton(Nz::Vector2f pos);

		void OnMouseMoved(int x, int y, int deltaX, int deltaY) override;
		void OnMouseButtonPress(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseExit() override;

		Ndk::EntityHandle m_topButtonEntity;
		Ndk::EntityHandle m_bottomButtonEntity;
		Ndk::EntityHandle m_cursorEntity;

		Nz::SpriteRef m_topButtonSprite;
		Nz::SpriteRef m_bottomButtonSprite;
		Nz::SpriteRef m_CursorSprite;

		static Nz::Color s_buttonBaseColor;
		static Nz::Color s_buttonHoveredColor;
		static Nz::Color s_buttonPressedColor;
		static Nz::Color s_cursorColor;
		static Nz::Color s_cursorHoveredColor;
		static Nz::Color s_cursorPressedColor;
		static float s_cursorMoveSpeed;

		float m_minValue;
		float m_maxValue;
		float m_value;
		float m_valueSize;
		PressedButton m_pressedButton;
		ScrollBarOrientation m_orientation;
	};
}

#include <NDK/Widgets/ScrollBarWidget.inl>

#endif // !NDK_WIDGETS_SCROLLBARWIDGET_HPP
