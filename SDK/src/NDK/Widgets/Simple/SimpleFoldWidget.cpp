#include <NDK/Widgets/Simple/SimpleFoldWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>

namespace Ndk
{
	const std::string SimpleFoldWidget::s_ArrowFolded("Ndk::SimpleFoldWidget::ArrowFolded");
	const std::string SimpleFoldWidget::s_ArrowFoldedHovered("Ndk::SimpleFoldWidget::ArrowFoldedHovered");
	const std::string SimpleFoldWidget::s_ArrowOpened("Ndk::SimpleFoldWidget::ArrowOpened");
	const std::string SimpleFoldWidget::s_ArrowOpenedHovered("Ndk::SimpleFoldWidget::ArrowOpenedHovered");
	const std::string SimpleFoldWidget::s_ArrowDisabled("Ndk::SimpleFoldWidget::ArrowDisabled");
	const std::string SimpleFoldWidget::s_Hover("Ndk::SimpleFoldWidget::Hover");

	SimpleFoldWidget::TextureInfo::TextureInfo()
		: color{ 255, 255, 255 }
		, textureCoords{ 0.f, 0.f, 1.f, 1.f }
	{

	}

	SimpleFoldWidget::SimpleFoldWidget(BaseWidget* parent)
		: BaseWidget(parent)
		, m_hovered{ false }
		, m_folded{true}
		, m_contentMargin{10}
		, m_contentOffset{20}
		, m_textMargin{10}
		, m_areaWidget{nullptr}
	{
		int parentRenderOrderIndex = BaseWidget::GetRenderOrderIndex();

		m_arrowSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));

		m_arrowEntity = CreateEntity();
		m_arrowEntity->AddComponent<NodeComponent>().SetParent(this);
		m_arrowEntity->AddComponent<GraphicsComponent>().Attach(m_arrowSprite, parentRenderOrderIndex + 2);

		m_hoverSprite = Nz::SlicedSprite::New();
		Nz::MaterialRef mat = Nz::Material::New("Translucent2D");
		mat->GetDiffuseSampler().SetAnisotropyLevel(10);
		m_hoverSprite->SetMaterial(mat);

		m_hoverEntity = CreateEntity();
		m_hoverEntity->AddComponent<NodeComponent>().SetParent(this);
		m_hoverEntity->AddComponent<GraphicsComponent>().Attach(m_hoverSprite, parentRenderOrderIndex + 1);

		m_textSprite = Nz::TextSprite::New();

		m_textEntity = CreateEntity();
		m_textEntity->AddComponent<NodeComponent>().SetParent(this);
		m_textEntity->AddComponent<GraphicsComponent>().Attach(m_textSprite, parentRenderOrderIndex + 3);

		SetArrowTexture(Nz::TextureLibrary::Get(s_ArrowFolded), FoldState_Folded);
		SetArrowTexture(Nz::TextureLibrary::Get(s_ArrowFoldedHovered), FoldState_FoldedHovered);
		SetArrowTexture(Nz::TextureLibrary::Get(s_ArrowOpened), FoldState_Opened);
		SetArrowTexture(Nz::TextureLibrary::Get(s_ArrowOpenedHovered), FoldState_OpenedHovered);
		SetArrowTexture(Nz::TextureLibrary::Get(s_ArrowDisabled), FoldState_Disabled);

		SetHoverTexture(Nz::TextureLibrary::Get(s_Hover), FoldState_FoldedHovered);
		SetHoverTexture(Nz::TextureLibrary::Get(s_Hover), FoldState_OpenedHovered);

		SetHoverSliceMargin(12.f / m_hoverDatas[FoldState_OpenedHovered].texture->GetWidth());

		UpdateSize();
	}

	bool SimpleFoldWidget::Initialize()
	{

		const Nz::UInt8 r_hover[] =
		{
			#include <NDK/Resources/Widgets/Hover.png.h>
		};

		const Nz::UInt8 r_arrowFolded[] =
		{
			#include <NDK/Resources/Widgets/FoldArrowFolded.png.h>
		};

		const Nz::UInt8 r_arrowFoldedHovered[] =
		{
			#include <NDK/Resources/Widgets/FoldArrowFoldedHovered.png.h>
		};

		const Nz::UInt8 r_arrowOpened[] =
		{
			#include <NDK/Resources/Widgets/FoldArrowOpened.png.h>
		};

		const Nz::UInt8 r_arrowOpenedHovered[] =
		{
			#include <NDK/Resources/Widgets/FoldArrowOpenedHovered.png.h>
		};

		const Nz::UInt8 r_arrowDisabled[] =
		{
			#include <NDK/Resources/Widgets/FoldArrowDisabled.png.h>
		};

		Nz::TextureRef hoverTexture = Nz::Texture::LoadFromMemory(r_hover, sizeof(r_hover) / sizeof(r_hover[0]));
		if (!hoverTexture)
		{
			NazaraError("Failed to load embedded Widgets/Hover.png");
			return false;
		}

		Nz::TextureRef arrowFoldedTexture = Nz::Texture::LoadFromMemory(r_arrowFolded, sizeof(r_arrowFolded) / sizeof(r_arrowFolded[0]));
		if (!arrowFoldedTexture)
		{
			NazaraError("Failed to load embedded Widgets/FoldArrowFolded.png");
			return false;
		}

		Nz::TextureRef arrowFoldedHoveredTexture = Nz::Texture::LoadFromMemory(r_arrowFoldedHovered, sizeof(r_arrowFoldedHovered) / sizeof(r_arrowFoldedHovered[0]));
		if (!arrowFoldedHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/FoldArrowFoldedHovered.png");
			return false;
		}

		Nz::TextureRef arrowOpenedTexture = Nz::Texture::LoadFromMemory(r_arrowOpened, sizeof(r_arrowOpened) / sizeof(r_arrowOpened[0]));
		if (!arrowOpenedTexture)
		{
			NazaraError("Failed to load embedded Widgets/FoldArrowOpened.png");
			return false;
		}

		Nz::TextureRef arrowOpenedHoveredTexture = Nz::Texture::LoadFromMemory(r_arrowOpenedHovered, sizeof(r_arrowOpenedHovered) / sizeof(r_arrowOpenedHovered[0]));
		if (!arrowOpenedHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/FoldArrowOpenedHovered.png");
			return false;
		}

		Nz::TextureRef arrowDisabledTexture = Nz::Texture::LoadFromMemory(r_arrowDisabled, sizeof(r_arrowDisabled) / sizeof(r_arrowDisabled[0]));
		if (!arrowDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/FoldArrowDisabled.png");
			return false;
		}

		Nz::TextureLibrary::Register(s_Hover, std::move(hoverTexture));
		Nz::TextureLibrary::Register(s_ArrowFolded, std::move(arrowFoldedTexture));
		Nz::TextureLibrary::Register(s_ArrowFoldedHovered, std::move(arrowFoldedHoveredTexture));
		Nz::TextureLibrary::Register(s_ArrowOpened, std::move(arrowOpenedTexture));
		Nz::TextureLibrary::Register(s_ArrowOpenedHovered, std::move(arrowOpenedHoveredTexture));
		Nz::TextureLibrary::Register(s_ArrowDisabled, std::move(arrowDisabledTexture));

		return true;
	}

	void SimpleFoldWidget::Uninitialize()
	{
		Nz::TextureLibrary::Unregister(s_Hover);
		Nz::TextureLibrary::Unregister(s_ArrowFolded);
		Nz::TextureLibrary::Unregister(s_ArrowFoldedHovered);
		Nz::TextureLibrary::Unregister(s_ArrowOpened);
		Nz::TextureLibrary::Unregister(s_ArrowOpenedHovered);
		Nz::TextureLibrary::Unregister(s_ArrowDisabled);
	}

	void SimpleFoldWidget::Layout()
	{
		Nz::Rectf foldRect = GetFoldRect();
		Nz::Rectf contentRect = GetContentRect();

		FoldState state = GetState();

		TextureInfo & arrowTexture = m_arrowDatas[state];
		TextureInfo & hoverTexture = m_hoverDatas[state];

		bool isVisible = IsVisible();

		m_arrowEntity->Enable(arrowTexture.texture.IsValid() && isVisible);
		if (arrowTexture.texture.IsValid())
		{
			m_arrowSprite->SetTexture(arrowTexture.texture, false);
			m_arrowSprite->SetTextureCoords(arrowTexture.textureCoords);
			m_arrowSprite->SetColor(arrowTexture.color);
			Nz::Vector3ui texSize = arrowTexture.texture->GetSize();

			m_arrowSprite->SetSize(texSize.x * arrowTexture.textureCoords.width, texSize.y * arrowTexture.textureCoords.height);
		}

		m_hoverEntity->Enable(hoverTexture.texture.IsValid() && isVisible);
		if (hoverTexture.texture.IsValid())
		{
			m_hoverSprite->SetTexture(hoverTexture.texture, false);
			m_hoverSprite->SetTextureCoords(hoverTexture.textureCoords);
			m_hoverSprite->SetColor(hoverTexture.color);
			m_hoverSprite->SetSize(foldRect.width, foldRect.height);
		}

		m_textEntity->GetComponent<Ndk::NodeComponent>().SetPosition(GetTextPosition());
		m_arrowEntity->GetComponent<Ndk::NodeComponent>().SetPosition(m_textMargin, m_textMargin);
		m_hoverEntity->GetComponent<Ndk::NodeComponent>().SetPosition(0, 0);
		
		if (m_areaWidget != nullptr)
			m_areaWidget->SetPosition(Nz::Vector2f(contentRect.x, contentRect.y));
	}

	void SimpleFoldWidget::Resize(const Nz::Vector2f& size)
	{
		Nz::Vector2f newSize = size;
		newSize.Maximize(GetMinimumSize());
		newSize.Minimize(GetMaximumSize());

		SetSize(newSize);

		Layout();

		if (m_areaWidget != nullptr)
		{
			Nz::Rectf contentRect = GetContentRect();
			BaseWidget::Resize(*m_areaWidget, Nz::Vector2f(contentRect.width, contentRect.height));
		}
	}

	int SimpleFoldWidget::GetRenderOrderIndex() const
	{
		//the arrow, the text and the hover
		return BaseWidget::GetRenderOrderIndex() + 3;
	}

	FoldState SimpleFoldWidget::GetState() const
	{
		if (!IsEnabled())
			return FoldState_Disabled;
		else
		{
			if (IsFolded())
			{
				if (IsHovered())
					return FoldState_FoldedHovered;
				else return FoldState_Folded;
			}
			else
			{
				if (IsHovered())
					return FoldState_OpenedHovered;
				else return FoldState_Opened;
			}
		}
	}

	void SimpleFoldWidget::UpdateSize()
	{
		ChildResized();
	}

	void SimpleFoldWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{
		Nz::Rectf rect = GetFoldRect();

		SetHovered(rect.Contains(static_cast<float>(x), static_cast<float>(y)));
	}

	void SimpleFoldWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{
		Nz::Rectf rect = GetFoldRect();

		if (rect.Contains(static_cast<float>(x), static_cast<float>(y)))
			SetFolded(!IsFolded());
	}

	void SimpleFoldWidget::OnMouseExit()
	{
		SetHovered(false);
	}

	void SimpleFoldWidget::OnUpdatePreferredSize()
	{
		Nz::Vector2f size = CalculateFoldSize();

		if (IsFolded() || m_areaWidget == nullptr)
		{
			SetPreferredSize(size, false);
			return;
		}

		Nz::Vector2f areaSize = m_areaWidget->GetPreferredSize();

		areaSize.x += m_contentOffset;
		size.x = std::max(size.x, areaSize.x);
		size.y += m_contentMargin + areaSize.y;

		SetPreferredSize(size, false);
	}

	Nz::Rectf SimpleFoldWidget::GetFoldRect() const
	{
		Nz::Vector2f size = GetSize();

		Nz::Vector2f foldSize = CalculateFoldSize();

		size.y = std::min(size.y, foldSize.y);

		return Nz::Rectf(0, 0, size.x, size.y);
	}


	Nz::Vector2f SimpleFoldWidget::GetTextPosition() const
	{
		Nz::Boxf textBox = m_textEntity->GetComponent<GraphicsComponent>().GetAABB();

		FoldState state = GetState();

		const TextureInfo & arrowInfo = m_arrowDatas[state];
		Nz::Vector2f arrowSize(0, 0);
		if (arrowInfo.texture.IsValid())
		{
			Nz::Vector3ui texSize = arrowInfo.texture->GetSize();
			arrowSize.x = texSize.x * arrowInfo.textureCoords.width;
			arrowSize.y = texSize.y * arrowInfo.textureCoords.height;
		}

		float height = std::max(textBox.height, arrowSize.y);
		float x = arrowSize.x > 0 ? arrowSize.x + m_textMargin : 0;

		return Nz::Vector2f(x + m_textMargin, (height - textBox.height) / 2 + m_textMargin);
	}

	Nz::Rectf SimpleFoldWidget::GetContentRect() const
	{
		if (IsFolded())
			return Nz::Rectf(0, 0, 0, 0);

		Nz::Vector2f size = GetSize();
		Nz::Rectf foldRect = GetFoldRect();

		return Nz::Rectf(m_contentOffset, foldRect.height + m_contentMargin, size.x - m_contentOffset, size.y - foldRect.height - m_contentMargin);
	}

	Nz::Vector2f SimpleFoldWidget::CalculateFoldSize() const
	{
		Nz::Boxf textBox = m_textEntity->GetComponent<GraphicsComponent>().GetAABB();

		FoldState state = GetState();

		const TextureInfo & arrowInfo = m_arrowDatas[state];
		Nz::Vector2f arrowSize(0, 0);
		if (arrowInfo.texture.IsValid())
		{
			Nz::Vector3ui texSize = arrowInfo.texture->GetSize();
			arrowSize.x = texSize.x * arrowInfo.textureCoords.width;
			arrowSize.y = texSize.y * arrowInfo.textureCoords.height;
		}

		Nz::Vector2f size;
		if (arrowSize.x > 0)
			size.x = arrowSize.x + textBox.width + m_textMargin * 3;
		else size.x = textBox.width + m_textMargin * 2;
		size.y = std::max(arrowSize.y, textBox.height) + m_textMargin * 2;

		return size;
	}
}
