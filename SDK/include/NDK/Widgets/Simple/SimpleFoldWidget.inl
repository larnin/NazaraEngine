#include <NDK/Widgets/Simple/SimpleFoldWidget.hpp>

namespace Ndk
{
	template<typename T, typename... Args>
	T* SimpleFoldWidget::CreateAreaWidget(Args&&... args)
	{
		if (m_areaWidget != nullptr)
			m_areaWidget->Destroy();

		T* widget = Add<T>(std::forward<Args>(args)...);
		m_areaWidget = widget;

		if (IsFolded())
			m_areaWidget->Show(false);

		return widget;
	}

	inline BaseWidget* SimpleFoldWidget::GetAreaWidget()
	{
		return m_areaWidget;
	}

	inline void SimpleFoldWidget::UpdateText(const Nz::AbstractTextDrawer& drawer)
	{
		m_textSprite->Update(drawer);

		UpdateSize();
	}

	inline void SimpleFoldWidget::SetFolded(bool folded)
	{
		if (m_folded == folded)
			return;

		m_folded = folded;

		UpdateSize();

		if (m_areaWidget != nullptr)
			m_areaWidget->Show(!folded);

		OnFold(m_folded);
	}

	inline void SimpleFoldWidget::SetHovered(bool hovered)
	{
		if (m_hovered == hovered)
			return;

		m_hovered = hovered;

		OnHover(m_hovered);

		Layout();
	}

	inline void SimpleFoldWidget::SetContentOffset(float offset)
	{
		m_contentOffset = offset;

		if (!IsFolded())
			UpdateSize();
	}

	inline void SimpleFoldWidget::SetContentMargin(float margin)
	{
		m_contentMargin = margin;

		if (!IsFolded())
			UpdateSize();
	}

	inline void SimpleFoldWidget::SetTextMargin(float margin)
	{
		m_textMargin = margin;

		UpdateSize();
	}

	inline void SimpleFoldWidget::SetArrowTexture(Nz::TextureRef texture, FoldState state)
	{
		if (state == FoldState::FoldState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_arrowDatas[i].texture = texture;

			Layout();
			return;
		}

		NazaraAssert(state <= FoldState_Max, "You can't set any texture on this FoldState");

		m_arrowDatas[state].texture = texture;

		Layout();
	}

	inline void SimpleFoldWidget::SetArrowTextureCoord(const Nz::Rectf & coord, FoldState state)
	{
		if (state == FoldState::FoldState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_arrowDatas[i].textureCoords = coord;

			Layout();
			return;
		}

		NazaraAssert(state <= FoldState_Max, "You can't set any texture on this FoldState");

		m_arrowDatas[state].textureCoords = coord;

		Layout();
	}

	inline void SimpleFoldWidget::SetArrowTextureRect(const Nz::Rectui & rect, FoldState state)
	{
		if (state == FoldState::FoldState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
			{
				NazaraAssert(m_arrowDatas[i].texture, "No texture defined on this FoldState");

				Nz::Vector3ui texSize = m_arrowDatas[i].texture->GetSize();

				m_arrowDatas[i].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
					static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);
			}

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this FoldState");

		NazaraAssert(m_arrowDatas[state].texture, "No texture defined on this FoldState");

		Nz::Vector3ui texSize = m_arrowDatas[state].texture->GetSize();

		m_arrowDatas[state].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);

		Layout();
	}

	inline void SimpleFoldWidget::SetArrowColor(const Nz::Color & color, FoldState state)
	{
		if (state == FoldState::FoldState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_arrowDatas[i].color = color;

			Layout();
			return;
		}

		NazaraAssert(state <= FoldState_Max, "You can't set any texture on this FoldState");

		m_arrowDatas[state].color = color;

		Layout();
	}

	inline void SimpleFoldWidget::SetHoverTexture(Nz::TextureRef texture, FoldState state)
	{
		if (state == FoldState::FoldState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_hoverDatas[i].texture = texture;

			Layout();
			return;
		}

		NazaraAssert(state <= FoldState_Max, "You can't set any texture on this FoldState");

		m_hoverDatas[state].texture = texture;

		Layout();
	}

	inline void SimpleFoldWidget::SetHoverTextureCoord(const Nz::Rectf & coord, FoldState state)
	{
		if (state == FoldState::FoldState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_hoverDatas[i].textureCoords = coord;

			Layout();
			return;
		}

		NazaraAssert(state <= FoldState_Max, "You can't set any texture on this FoldState");

		m_hoverDatas[state].textureCoords = coord;

		Layout();
	}

	inline void SimpleFoldWidget::SetHoverTextureRect(const Nz::Rectui & rect, FoldState state)
	{
		if (state == FoldState::FoldState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
			{
				NazaraAssert(m_hoverDatas[i].texture, "No texture defined on this FoldState");

				Nz::Vector3ui texSize = m_hoverDatas[i].texture->GetSize();

				m_hoverDatas[i].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
					static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);
			}

			Layout();
			return;
		}

		NazaraAssert(state <= ButtonState_Max, "You can't set any texture coords on this FoldState");

		NazaraAssert(m_hoverDatas[state].texture, "No texture defined on this FoldState");

		Nz::Vector3ui texSize = m_hoverDatas[state].texture->GetSize();

		m_hoverDatas[state].textureCoords = Nz::Rectf(static_cast<float>(rect.x) / texSize.x, static_cast<float>(rect.y) / texSize.y,
			static_cast<float>(rect.width) / texSize.x, static_cast<float>(rect.height) / texSize.y);

		Layout();
	}

	inline void SimpleFoldWidget::SetHoverColor(const Nz::Color & color, FoldState state)
	{
		if (state == FoldState::FoldState_All)
		{
			for (unsigned int i = 0; i <= ButtonState_Max; i++)
				m_hoverDatas[i].color = color;

			Layout();
			return;
		}

		NazaraAssert(state <= FoldState_Max, "You can't set any texture on this FoldState");

		m_hoverDatas[state].color = color;

		Layout();
	}

	inline void SimpleFoldWidget::SetHoverSliceMargin(float size)
	{
		m_hoverSprite->SetSliceMargin(size);
	}

	inline void SimpleFoldWidget::SetHoverSliceMargin(unsigned int size)
	{
		m_hoverSprite->SetSliceMargin(size);
	}

	inline void SimpleFoldWidget::SetHoverSliceMargin(float top, float down, float left, float right)
	{
		m_hoverSprite->SetSliceMargin(top, down, left, right);
	}

	inline void SimpleFoldWidget::SetHoverSliceMargin(unsigned int top, unsigned int down, unsigned int left, unsigned int right)
	{
		m_hoverSprite->SetSliceMargin(top, down, left, right);
	}

	inline bool SimpleFoldWidget::IsFolded() const
	{
		return m_folded;
	}

	inline bool SimpleFoldWidget::IsHovered() const
	{
		return m_hovered;
	}

	inline float SimpleFoldWidget::GetContentOffset() const
	{
		return m_contentOffset;
	}

	inline float SimpleFoldWidget::GetContentMargin() const
	{
		return m_contentMargin;
	}

	inline float SimpleFoldWidget::GetTextMargin() const
	{
		return m_textMargin;
	}

	inline Nz::TextureRef SimpleFoldWidget::GetArrowTexture(FoldState state) const
	{
		NazaraAssert(state <= FoldState_Max, "You can't get any texture on this FoldState");

		return m_arrowDatas[state].texture;
	}

	inline Nz::Rectf SimpleFoldWidget::GetArrowTextureCoord(FoldState state) const
	{
		NazaraAssert(state <= FoldState_Max, "You can't get any texture on this FoldState");

		return m_arrowDatas[state].textureCoords;
	}

	inline Nz::Color SimpleFoldWidget::GetArrowColor(FoldState state) const
	{
		NazaraAssert(state <= FoldState_Max, "You can't get any texture on this FoldState");

		return m_arrowDatas[state].color;
	}

	inline Nz::TextureRef SimpleFoldWidget::GetHoverTexture(FoldState state) const
	{
		NazaraAssert(state <= FoldState_Max, "You can't get any texture on this FoldState");

		return m_hoverDatas[state].texture;
	}

	inline Nz::Rectf SimpleFoldWidget::GetHoverTextureCoord(FoldState state) const
	{
		NazaraAssert(state <= FoldState_Max, "You can't get any texture on this FoldState");

		return m_hoverDatas[state].textureCoords;
	}

	inline Nz::Color SimpleFoldWidget::GetHoverColor(FoldState state) const
	{
		NazaraAssert(state <= FoldState_Max, "You can't get any texture on this FoldState");

		return m_hoverDatas[state].color;
	}
}
