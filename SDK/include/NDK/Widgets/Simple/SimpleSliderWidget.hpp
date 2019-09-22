#pragma once

#ifndef NDK_WIDGETS_SIMPLESLIDERWIDGET_HPP
#define NDK_WIDGETS_SIMPLESLIDERWIDGET_HPP

#include <NDK/Widgets/Base/BaseSliderWidget.hpp>
#include <NDK/Widgets/Enums.hpp>
#include <Nazara/Core/Color.hpp>
#include <Nazara/Graphics/SlicedSprite.hpp>
#include <Nazara/Graphics/Sprite.hpp>
#include <Nazara/Graphics/TextSprite.hpp>
#include <Nazara/Utility/Font.hpp>

#include <array>

namespace Ndk
{
	class NDK_API SimpleSliderWidget : public BaseSliderWidget
	{
		friend class Sdk;

		struct TextureInfo
		{
			Nz::TextureRef texture;
			Nz::Color color;
			Nz::Rectf textureCoords;

			TextureInfo();
		};

	public:
		SimpleSliderWidget(BaseWidget* parent);
		SimpleSliderWidget(const SimpleSliderWidget&) = delete;
		SimpleSliderWidget(SimpleSliderWidget&&) = default;
		virtual ~SimpleSliderWidget() = default;

		int GetRenderOrderIndex() const override;

		inline void SetSliderTexture(Nz::TextureRef texture, SliderOrientation orientation, ButtonState state = ButtonState_All);
		inline void SetSliderTextureCoord(const Nz::Rectf & coord, SliderOrientation orientation, ButtonState state = ButtonState_All);
		inline void SetSliderTextureRect(const Nz::Rectui & rect, SliderOrientation orientation, ButtonState state = ButtonState_All);
		inline void SetSliderColor(const Nz::Color & color, SliderOrientation orientation, ButtonState state = ButtonState_All);

		inline void SetBackgroundTexture(Nz::TextureRef texture, SliderOrientation orientation, bool disabled);
		inline void SetBackgroundTextureCoord(const Nz::Rectf & coord, SliderOrientation orientation, bool disabled);
		inline void SetBackgroundTextureRect(const Nz::Rectui & rect, SliderOrientation orientation, bool disabled);
		inline void SetBackgroundColor(const Nz::Color & color, SliderOrientation orientation, bool disabled);

		inline void SetBackgroundMargin(float margin);

		inline void SetMoveSpeed(float speed);

		inline void EnableTextValue(bool enabled);
		inline void SetTextFont(const Nz::FontRef & font);
		inline void SetTextCharacterSize(unsigned int size);
		inline void SetTextStyle(Nz::TextStyleFlags style);
		inline void SetTextColor(Nz::Color color);
		inline void SetTextPosition(ButtonTextAlignment alignment);
		inline void SetTextMagin(float margin);
		inline void SetTextPrecision(unsigned int precision);

		inline Nz::TextureRef GetSliderTexture(SliderOrientation orientation, ButtonState state) const;
		inline Nz::Rectf GetSliderTextureCoord(SliderOrientation orientation, ButtonState state) const;
		inline Nz::Color GetSliderColor(SliderOrientation orientation, ButtonState state) const;
					
		inline Nz::TextureRef  GetBackgroundTexture(SliderOrientation orientation, bool disabled) const;
		inline Nz::Rectf GetBackgroundTextureCoord(SliderOrientation orientation, bool disabled) const;
		inline Nz::Color GetBackgroundColor(SliderOrientation orientation, bool disabled) const;
					
		inline float GetBackgroundMargin() const;

		inline float GetMoveSpeed() const;

		inline bool IsTextValueEnabled() const;
		inline Nz::FontRef GetTextFont() const;
		inline unsigned int GetTextCharacterSize() const;
		inline Nz::TextStyleFlags GetTextStyle() const;
		inline Nz::Color GetTextColor() const;
		inline ButtonTextAlignment GetTextPosition() const;
		inline float GetTextMargin() const;
		inline unsigned int GetTextPrecision() const;

		inline bool IsPressed() const;
		inline bool IsBackgroundPressed() const;
		inline bool IsHovered() const;

		NazaraSignal(OnPress, bool /*pressed*/);
		NazaraSignal(OnBackgroundPress, bool /*pressed*/);
		NazaraSignal(OnHover, bool /*hovered*/);

	protected:
		void Layout() override;
		void UpdatePreferedSize() override;

		inline void SetPressed(bool pressed);
		inline void SetBackgroundPressed(bool pressed);
		inline void SetHovered(bool hovered);

	private:
		ButtonState GetCurrentState() const;

		void OnMouseMoved(int x, int y, int deltaX, int deltaY) override;
		void OnMouseButtonPress(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseExit() override;
		void Update(float elapsedTime) override;

		inline Nz::Vector2f GetTextPos() const;
		inline Nz::Vector2f GetSliderPos() const;
		inline Nz::Vector2f GetSliderSize() const;

		Nz::Rectf GetButtonRect() const;

		void UpdateTextSize();
		void UpdateText();

		static bool Initialize();
		static void Uninitialize();

		EntityHandle m_backEntity;
		Nz::SlicedSpriteRef m_backSprite;
		EntityHandle m_sliderEntity;
		Nz::SpriteRef m_sliderSprite;
		EntityHandle m_textEntity;
		Nz::TextSpriteRef m_textSprite;

		bool m_hovered;
		bool m_pressed;
		bool m_backgroundPressed;
		float m_pressOffset;
		float m_moveSpeed;

		bool m_textEnabled;
		Nz::FontRef m_textFont;
		unsigned int m_textCharacterSize;
		Nz::TextStyleFlags m_textStyle;
		Nz::Color m_textColor;
		ButtonTextAlignment m_textPosition;
		float m_textMargin;
		unsigned int m_textPrecision;
		Nz::Vector2f m_textMaxSize;
		Nz::Vector2f m_textSize;

		std::array<std::array<TextureInfo, ButtonState_Max + 1>, SliderOrientation_Max + 1> m_sliderDatas;
		std::array<TextureInfo, SliderOrientation_Max + 1> m_back;
		std::array<TextureInfo, SliderOrientation_Max + 1> m_backDisabled;
		float m_backMargin;

		static const std::string s_sliderBackHorizontalName;
		static const std::string s_sliderBackHorizontalDisabledName;
		static const std::string s_sliderHorizontalName;
		static const std::string s_sliderHorizontalHoveredName;
		static const std::string s_sliderHorizontalPressedName;
		static const std::string s_sliderHorizontalDisabledName;
		static const std::string s_sliderBackVerticalName;
		static const std::string s_sliderBackVerticalDisabledName;
		static const std::string s_sliderVerticalName;
		static const std::string s_sliderVerticalHoveredName;
		static const std::string s_sliderVerticalPressedName;
		static const std::string s_sliderVerticalDisabledName;
	};
}

#include <NDK/Widgets/Simple/SimpleSliderWidget.inl>

#endif //NDK_WIDGETS_TEXTUREDBUTTONWIDGET_HPP
