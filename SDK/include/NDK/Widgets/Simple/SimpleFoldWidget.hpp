#pragma once

#ifndef NDK_WIDGETS_SIMPLEFOLDWIDGET_HPP
#define NDK_WIDGETS_SIMPLEFOLDWIDGET_HPP

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/Widgets/Enums.hpp>
#include <Nazara/Graphics/Sprite.hpp>
#include <Nazara/Graphics/SlicedSprite.hpp>
#include <Nazara/Graphics/TextSprite.hpp>

#include <array>

namespace Ndk
{
	class NDK_API SimpleFoldWidget : public BaseWidget
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
		SimpleFoldWidget(BaseWidget* parent);
		SimpleFoldWidget(const SimpleFoldWidget&) = delete;
		SimpleFoldWidget(SimpleFoldWidget&&) = default;
		virtual ~SimpleFoldWidget() = default;

		int GetRenderOrderIndex() const override;

		template<typename T, typename... Args>
		T* CreateAreaWidget(Args&&... args);
		inline BaseWidget* GetAreaWidget();

		inline void UpdateText(const Nz::AbstractTextDrawer& drawer);

		inline void SetFolded(bool folded);

		inline void SetContentOffset(float offset);
		inline void SetContentMargin(float margin);
		inline void SetTextMargin(float margin);

		inline void SetArrowTexture(Nz::TextureRef texture, FoldState state = FoldState_All);
		inline void SetArrowTextureCoord(const Nz::Rectf & coord, FoldState state = FoldState_All);
		inline void SetArrowTextureRect(const Nz::Rectui & rect, FoldState state = FoldState_All);
		inline void SetArrowColor(const Nz::Color & color, FoldState state = FoldState_All);

		inline void SetHoverTexture(Nz::TextureRef texture, FoldState state = FoldState_All);
		inline void SetHoverTextureCoord(const Nz::Rectf & coord, FoldState state = FoldState_All);
		inline void SetHoverTextureRect(const Nz::Rectui & rect, FoldState state = FoldState_All);
		inline void SetHoverColor(const Nz::Color & color, FoldState state = FoldState_All);
		inline void SetHoverSliceMargin(float size);
		inline void SetHoverSliceMargin(unsigned int size);
		inline void SetHoverSliceMargin(float top, float down, float left, float right);
		inline void SetHoverSliceMargin(unsigned int top, unsigned int down, unsigned int left, unsigned int right);

		inline bool IsFolded() const;
		inline bool IsHovered() const;

		inline float GetContentOffset() const;
		inline float GetContentMargin() const;
		inline float GetTextMargin() const;

		inline Nz::TextureRef GetArrowTexture(FoldState state) const;
		inline Nz::Rectf GetArrowTextureCoord(FoldState state) const;
		inline Nz::Color GetArrowColor(FoldState state) const;

		inline Nz::TextureRef GetHoverTexture(FoldState state) const;
		inline Nz::Rectf GetHoverTextureCoord(FoldState state) const;
		inline Nz::Color GetHoverColor(FoldState state) const;

		NazaraSignal(OnHover, bool /*hovered*/);
		NazaraSignal(OnFold, bool /*folded*/);

	protected:
		virtual void Layout() override;
		virtual void Resize(const Nz::Vector2f& size) override;

	private:
		inline void SetHovered(bool hovered);

		FoldState GetState() const;
		void UpdateSize();

		void OnMouseMoved(int x, int y, int deltaX, int deltaY) override;
		void OnMouseButtonPress(int x, int y, Nz::Mouse::Button button) override;
		void OnMouseExit() override;
		void OnUpdatePreferredSize() override;

		Nz::Rectf GetFoldRect() const;
		Nz::Vector2f GetTextPosition() const;
		Nz::Rectf GetContentRect() const;
		Nz::Vector2f CalculateFoldSize() const;

		bool m_hovered;
		bool m_folded;
		float m_contentMargin;
		float m_contentOffset;
		float m_textMargin;

		std::array<TextureInfo, FoldState_Max + 1> m_arrowDatas;
		std::array<TextureInfo, FoldState_Max + 1> m_hoverDatas;

		EntityHandle m_textEntity;
		EntityHandle m_arrowEntity;
		EntityHandle m_hoverEntity;
		Nz::TextSpriteRef m_textSprite;
		Nz::SpriteRef m_arrowSprite;
		Nz::SlicedSpriteRef m_hoverSprite;

		BaseWidget * m_areaWidget;

		static bool Initialize();
		static void Uninitialize();

		static const std::string s_ArrowFolded;
		static const std::string s_ArrowFoldedHovered;
		static const std::string s_ArrowOpened;
		static const std::string s_ArrowOpenedHovered;
		static const std::string s_ArrowDisabled;
		static const std::string s_Hover;
	};
}

#include <NDK/Widgets/Simple/SimpleFoldWidget.inl>

#endif //NDK_WIDGETS_SIMPLEFOLDWIDGET_HPP
