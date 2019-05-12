#pragma once

#ifndef NDK_WIDGETS_FOLDABLEWIDGET_HPP
#define NDK_WIDGETS_FOLDABLEWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <Nazara/Graphics/Sprite.hpp>
#include <Nazara/Graphics/TextSprite.hpp>

namespace Nz
{
	class AbstractTextDrawer;
}

namespace Ndk
{
	class NDK_API FoldableWidget : public BaseWidget
	{
	public:
		FoldableWidget(BaseWidget* parent);
		FoldableWidget(const FoldableWidget&) = delete;
		FoldableWidget(FoldableWidget&&) = default;
		~FoldableWidget() = default;

		inline bool IsFolded() const;

		void SetFolded(bool folded);

		inline void UpdateText(const Nz::AbstractTextDrawer& drawer);

		template<typename T, typename... Args>
		T* CreateAreaWidget(Args&&... args);
		inline BaseWidget* GetAreaWidget();

		FoldableWidget& operator=(const FoldableWidget&) = delete;
		FoldableWidget& operator=(FoldableWidget&&) = default;

		NazaraSignal(OnFolded, const FoldableWidget* /*foldable*/);

	private:
		void OnLayout() override;

		void OnMouseMoved(int x, int y, int deltaX, int deltaY) override;
		void OnMouseButtonPress(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseExit() override;

		EntityHandle m_textEntity;
		EntityHandle m_buttonEntity;
		Nz::TextSpriteRef m_textSprite;
		Nz::SpriteRef m_buttonSprite;

		BaseWidget* m_areaWidget;

		bool m_folded;
		bool m_pressed;

		static Nz::Color s_buttonBaseColor;
		static Nz::Color s_buttonHoveredColor;
		static Nz::Color s_buttonPressedColor;
		static float s_spacing;
	};
}

#include <NDK/Widgets/FoldableWidget.inl>

#endif //NDK_WIDGETS_FOLDABLEWIDGET_HPP
