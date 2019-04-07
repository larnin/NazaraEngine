#pragma once

#ifndef NDK_WIDGETS_RADIOBUTTONWIDGET_HPP
#define NDK_WIDGETS_RADIOBUTTONWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <Nazara/Renderer/Texture.hpp>
#include <Nazara/Graphics/TextSprite.hpp>

namespace Nz
{
	class AbstractTextDrawer;
}

namespace Ndk
{
	class NDK_API RadioButtonWidget : public BaseWidget
	{
		friend class Sdk;

	public:
		RadioButtonWidget(BaseWidget* parent);
		RadioButtonWidget(const RadioButtonWidget&) = delete;
		RadioButtonWidget(RadioButtonWidget&&) = default;
		~RadioButtonWidget() = default;

		//virtual RadioButtonWidget* Clone() const = 0;

		inline void EnableRadioButton(bool enable = true);
		inline bool IsRadioButtonEnabled();

		inline const Nz::Vector2f& GetRadioButtonSize() const;
		inline bool GetState() const;
		inline float GetTextMargin() const;

		inline void SetRadioButtonSize(const Nz::Vector2f& size);
		void SetState(bool checked = true);
		inline void SetTextMargin(float margin);

		inline void UpdateText(const Nz::AbstractTextDrawer& drawer);


		RadioButtonWidget& operator=(const RadioButtonWidget&) = delete;
		RadioButtonWidget& operator=(RadioButtonWidget&&) = default;

		NazaraSignal(OnStateChanged, const RadioButtonWidget* /*radioButton*/);

	private:
		static bool Initialize();
		static void Uninitialize();

		void Layout() override;
		void UpdateRadioButton();
		void UpdateSize();

		void OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button) override;
		inline bool ContainsRadioButton(int x, int y) const;

		EntityHandle m_radioButtonBackgroundEntity;
		EntityHandle m_radioButtonContentEntity;
		EntityHandle m_textEntity;

		Nz::TextureRef m_background;
		Nz::TextureRef m_fill;

		Nz::SpriteRef m_radioButtonContentSprite;
		Nz::SpriteRef m_radioButtonBackgroundSprite;
		Nz::TextSpriteRef m_textSprite;

		static Nz::Color s_backgroundColor;
		static Nz::Color s_disabledBackgroundColor;

		bool m_radioButtonEnabled;

		float m_textMargin;
		bool m_state;
	};
}

#include <NDK/Widgets/RadioButtonWidget.inl>

#endif //NDK_WIDGETS_RADIOBUTTONWIDGET_HPP
