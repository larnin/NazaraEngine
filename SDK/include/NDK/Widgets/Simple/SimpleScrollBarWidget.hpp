#pragma once

#ifndef NDK_WIDGETS_SIMPLESCROLLBARWIDGET_HPP
#define NDK_WIDGETS_SIMPLESCROLLBARWIDGET_HPP

#include <NDK/Widgets/Base/BaseSliderWidget.hpp>
#include <NDK/Widgets/Enums.hpp>
#include <Nazara/Core/Color.hpp>
#include <Nazara/Graphics/SlicedSprite.hpp>
#include <Nazara/Graphics/Sprite.hpp>

#include <array>

namespace Ndk
{
	class NDK_API SimpleScrollBarWidget : public BaseSliderWidget
	{
		friend class Sdk;

		struct TextureInfo
		{
			Nz::TextureRef texture;
			Nz::Color color;
			Nz::Rectf textureCoords;

			TextureInfo();
		};

		enum PressedButton
		{
			PressedButton_More,
			PressedButton_Less,
			PressedButton_Center,
			PressedButton_Background,
			PressedButton_None
		};

	public:
		SimpleScrollBarWidget(BaseWidget* parent);
		SimpleScrollBarWidget(const SimpleScrollBarWidget&) = delete;
		SimpleScrollBarWidget(SimpleScrollBarWidget&&) = default;
		virtual ~SimpleScrollBarWidget() = default;

		int GetRenderOrderIndex() const override;

		inline void SetButtonTexture(Nz::TextureRef texture, ScrollBarButton button, ButtonState state = ButtonState_All);
		inline void SetButtonTextureCoord(const Nz::Rectf & coord, ScrollBarButton button, ButtonState state = ButtonState_All);
		inline void SetButtonTextureRect(const Nz::Rectui & rect, ScrollBarButton button, ButtonState state = ButtonState_All);
		inline void SetButtonColor(const Nz::Color & color, ScrollBarButton button, ButtonState state = ButtonState_All);

		inline void SetCenterButtonSliceMargin(float size);
		inline void SetCenterButtonSliceMargin(float top, float down, float left, float right);
		inline void SetCenterButtonSliceMargin(unsigned int top, unsigned int down, unsigned int left, unsigned int right);
		inline void SetCenterButtonSliceMargin(unsigned int size);

		inline void SetBackgroundTexture(Nz::TextureRef texture, SliderOrientation button);
		inline void SetBackgroundTextureCoord(const Nz::Rectf & coord, SliderOrientation button);
		inline void SetBackgroundTextureRect(const Nz::Rectui & rect, SliderOrientation button);
		inline void SetBackgroundColor(const Nz::Color & color, SliderOrientation button);

		inline void SetMoveSpeed(float speed);
		inline void SetMoveButtonSpeed(float speed);

		inline Nz::TextureRef GetButtonTexture(ScrollBarButton orientation, ButtonState state = ButtonState_All);
		inline Nz::Rectf GetButtonTextureCoord(ScrollBarButton orientation, ButtonState state = ButtonState_All);
		inline Nz::Color GetButtonColor(ScrollBarButton orientation, ButtonState state = ButtonState_All);
					
		inline Nz::TextureRef GetBackgroundTexture(SliderOrientation orientation);
		inline Nz::Rectf GetBackgroundTextureCoord(SliderOrientation orientation);
		inline Nz::Color GetBackgroundColor(SliderOrientation orientation);

		inline bool IsPressed() const;
		inline bool IsBackgroundPressed() const;
		inline bool IsButtonLessPressed() const;
		inline bool IsButtonMorePressed() const;
		inline bool IsHovered() const;
		inline bool IsButtonLessHovered() const;
		inline bool IsButtonMoreHovered() const;

		inline float GetMoveSpeed() const;
		inline float GetButtonMoveSpeed() const;

		NazaraSignal(OnPress, bool /*pressed*/);
		NazaraSignal(OnBackgroundPress, bool /*pressed*/);
		NazaraSignal(OnButtonLessPress, bool /*pressed*/);
		NazaraSignal(OnButtonMorePress, bool /*pressed*/);
		NazaraSignal(OnHover, bool /*hovered*/);
		NazaraSignal(OnButtonLessHover, bool /*hovered*/);
		NazaraSignal(OnButtonMoreHover, bool /*hovered*/);

	protected:
		void Layout() override;
		void UpdatePreferedSize() override;

		inline void SetPressed(bool pressed);
		inline void SetButtonMorePressed(bool pressed);
		inline void SetButtonLessPressed(bool pressed);
		inline void SetBackgroundPressed(bool pressed);
		inline void SetHovered(bool hovered);
		inline void SetButtonMoreHovered(bool hovered);
		inline void SetButtonLessHovered(bool hovered);

	private:
		ButtonState GetCurrentStateMoreButton() const;
		ButtonState GetCurrentStateLessButton() const;
		ButtonState GetCurrentStateCenterButton() const;
		Nz::Rectf GetSliderBounds() const;
		Nz::Rectf GetCenterButtonBounds() const;
		Nz::Rectf GetLessButtonBounds() const;
		Nz::Rectf GetMoreButtonBounds() const;

		void OnMouseMoved(int x, int y, int deltaX, int deltaY) override;
		void OnMouseButtonPress(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseExit() override;
		void Update(float elapsedTime) override;

		static bool Initialize();
		static void Uninitialize();

		bool m_hovered;
		bool m_buttonMoreHovered;
		bool m_buttonLessHovered;
		bool m_pressed;
		bool m_backgroundPressed;
		bool m_buttonMorePressed;
		bool m_buttonLessPressed;
		float m_pressOffset;
		float m_moveSpeed;
		float m_moveButtonSpeed;

		PressedButton m_currentPressedButton;

		std::array<std::array<TextureInfo, ButtonState_Max + 1>, ScrollBarButton_Max + 1> m_buttonsDatas;
		TextureInfo m_horizontalBackgroundDatas;
		TextureInfo m_verticalBackgroundDatas;

		EntityHandle m_backEntity;
		Nz::SpriteRef m_backSprite;
		EntityHandle m_centerButtonEntity;
		Nz::SlicedSpriteRef m_centerButtonSprite;
		EntityHandle m_moreButtonEntity;
		Nz::SpriteRef m_moreButtonSprite;
		EntityHandle m_lessButtonEntity;
		Nz::SpriteRef m_lessButtonSprite;

		static const std::string s_scrollCenterName;
		static const std::string s_scrollCenterHoveredName;
		static const std::string s_scrollCenterPressedName;
		static const std::string s_scrollCenterDisabledName;
		static const std::string s_scrollBackgroundHorizontalName;
		static const std::string s_scrollBackgroundVerticalName;
		static const std::string s_scrollLeftName;
		static const std::string s_scrollLeftHoveredName;
		static const std::string s_scrollLeftPressedName;
		static const std::string s_scrollLeftDisabledName;
		static const std::string s_scrollRightName;
		static const std::string s_scrollRightHoveredName;
		static const std::string s_scrollRightPressedName;
		static const std::string s_scrollRightDisabledName;
		static const std::string s_scrollUpName;
		static const std::string s_scrollUpHoveredName;
		static const std::string s_scrollUpPressedName;
		static const std::string s_scrollUpDisabledName;
		static const std::string s_scrollDownName;
		static const std::string s_scrollDownHoveredName;
		static const std::string s_scrollDownPressedName;
		static const std::string s_scrollDownDisabledName;
	};
}

#include <NDK/Widgets/Simple/SimpleScrollBarWidget.inl>

#endif //NDK_WIDGETS_SIMPLESCROLLBARWIDGET_HPP
