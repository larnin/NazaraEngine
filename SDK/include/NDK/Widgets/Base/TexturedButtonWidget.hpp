#pragma once

#ifndef NDK_WIDGETS_TEXTUREDBUTTONWIDGET_HPP
#define NDK_WIDGETS_TEXTUREDBUTTONWIDGET_HPP

#include <NDK/Widgets/Base/BaseButtonWidget.hpp>
#include <NDK/Widgets/Enums.hpp>
#include <Nazara/Core/Color.hpp>
#include <Nazara/Graphics/SlicedSprite.hpp>
#include <Nazara/Graphics/TextSprite.hpp>

#include <array>

namespace Ndk
{
	class NDK_API TexturedButtonWidget : public BaseButtonWidget
	{
	protected:
		struct ButtonInfo
		{
			Nz::TextureRef texture;
			Nz::Color color;
			Nz::Rectf textureCoords;

			ButtonInfo();
		};

	public:
		TexturedButtonWidget(BaseWidget* parent);
		TexturedButtonWidget(const TexturedButtonWidget&) = delete;
		TexturedButtonWidget(TexturedButtonWidget&&) = default;
		virtual ~TexturedButtonWidget() = default;

		inline void SetSliceMargin(float size);
		inline void SetSliceMargin(unsigned int size);
		inline void SetSliceMargin(float top, float down, float left, float right);
		inline void SetSliceMargin(unsigned int top, unsigned int down, unsigned int left, unsigned int right);

		int GetRenderOrderIndex() const override;

		inline Nz::TextureRef GetTexture(ButtonState state) const;
		inline Nz::Rectf GetTextureCoord(ButtonState state) const;
		inline Nz::Color GetTextureColor(ButtonState state) const;
		inline Nz::Vector2f GetButtonSize() const;
		inline ButtonTextAlignment GetTextAlignment() const;
		inline ButtonTextAlignment GetTextPosition() const;
		inline float GetTextMargin() const;
		inline bool HasKeepTextureRatio() const;

		inline bool IsButtonHovered() const;

		inline void SetTexture(Nz::TextureRef texture, ButtonState state = ButtonState_All);
		inline void SetTextureCoord(const Nz::Rectf & coord, ButtonState state = ButtonState_All);
		inline void SetTextureRect(const Nz::Rectui & rect, ButtonState state = ButtonState_All);
		inline void SetButtonColor(const Nz::Color & color, ButtonState state = ButtonState_All);
		inline void SetTextAlignment(ButtonTextAlignment alignment);
		inline void SetTextPosition(ButtonTextAlignment position);
		inline void SetTextMargin(float margin);
		inline void SetKeepTextureRatio(bool keepRatio);

		inline void UpdateText(const Nz::AbstractTextDrawer& drawer);

	protected:
		Nz::Vector2f GetTextPos() const;
		Nz::Vector2f GetTextAlignmentOffset() const;
		Nz::Vector2f GetButtonPos() const;
		inline void SetButtonSize(Nz::Vector2f size);
		Nz::Rectf GetButtonRect() const;

		virtual void Layout() override;

	private:
		void OnMouseMoved(int x, int y, int deltaX, int deltaY) override;
		void OnMouseButtonPress(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseExit() override;

		void UpdateSize();
		void UpdateState();

		EntityHandle m_buttonEntity;
		Nz::SlicedSpriteRef m_buttonSprite;
		std::array<ButtonInfo, ButtonState_Max + 1> m_buttonsDatas;
		bool m_keepTextureRatio;

		EntityHandle m_textEntity;
		Nz::TextSpriteRef m_textSprite;
		ButtonTextAlignment m_textAlignment;
		ButtonTextAlignment m_textPosition;
		float m_textMargin;
		bool m_hovered;

		ButtonState m_currentButtonState;

	};
}

#include <NDK/Widgets/Base/TexturedButtonWidget.inl>

#endif //NDK_WIDGETS_TEXTUREDBUTTONWIDGET_HPP
