#include <NDK/Widgets/Simple/SimpleScrollBarWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>

#include <iostream>

namespace Ndk
{
	const std::string SimpleScrollBarWidget::s_scrollCenterName("Ndk::ScrollBar::Center");
	const std::string SimpleScrollBarWidget::s_scrollCenterHoveredName("Ndk::ScrollBar::CenterHovered");
	const std::string SimpleScrollBarWidget::s_scrollCenterPressedName("Ndk::ScrollBar::CenterPressed");
	const std::string SimpleScrollBarWidget::s_scrollCenterDisabledName("Ndk::ScrollBar::CenterDisabled");
	const std::string SimpleScrollBarWidget::s_scrollBackgroundHorizontalName("Ndk::ScrollBar::BackgroundHorizontal");
	const std::string SimpleScrollBarWidget::s_scrollBackgroundVerticalName("Ndk::ScrollBar::BackgroundVertical");
	const std::string SimpleScrollBarWidget::s_scrollLeftName("Ndk::ScrollBar::Left");
	const std::string SimpleScrollBarWidget::s_scrollLeftHoveredName("Ndk::ScrollBar::LeftHovered");
	const std::string SimpleScrollBarWidget::s_scrollLeftPressedName("Ndk::ScrollBar::LeftPressed");
	const std::string SimpleScrollBarWidget::s_scrollLeftDisabledName("Ndk::ScrollBar::LeftDisabled");
	const std::string SimpleScrollBarWidget::s_scrollRightName("Ndk::ScrollBar::Right");
	const std::string SimpleScrollBarWidget::s_scrollRightHoveredName("Ndk::ScrollBar::RightHovered");
	const std::string SimpleScrollBarWidget::s_scrollRightPressedName("Ndk::ScrollBar::RightPressed");
	const std::string SimpleScrollBarWidget::s_scrollRightDisabledName("Ndk::ScrollBar::RightDisabled");
	const std::string SimpleScrollBarWidget::s_scrollUpName("Ndk::ScrollBar::Up");
	const std::string SimpleScrollBarWidget::s_scrollUpHoveredName("Ndk::ScrollBar::UpHovered");
	const std::string SimpleScrollBarWidget::s_scrollUpPressedName("Ndk::ScrollBar::UpPressed");
	const std::string SimpleScrollBarWidget::s_scrollUpDisabledName("Ndk::ScrollBar::UpDisabled");
	const std::string SimpleScrollBarWidget::s_scrollDownName("Ndk::ScrollBar::Down");
	const std::string SimpleScrollBarWidget::s_scrollDownHoveredName("Ndk::ScrollBar::DownHovered");
	const std::string SimpleScrollBarWidget::s_scrollDownPressedName("Ndk::ScrollBar::DownPressed");
	const std::string SimpleScrollBarWidget::s_scrollDownDisabledName("Ndk::ScrollBar::DownDisabled");

	SimpleScrollBarWidget::TextureInfo::TextureInfo() :
		color{ 255, 255, 255 },
		textureCoords{ 0.f, 0.f, 1.f, 1.f }
	{

	}

	SimpleScrollBarWidget::SimpleScrollBarWidget(BaseWidget* parent):
	BaseSliderWidget(parent),
	m_hovered{false},
	m_buttonMoreHovered{false},
	m_buttonLessHovered{false},
	m_pressed{false},
	m_backgroundPressed{false},
	m_buttonMorePressed{false},
	m_buttonLessPressed{false},
	m_pressOffset{0},
	m_moveSpeed{250},
	m_moveButtonSpeed{50},
	m_currentPressedButton{PressedButton_None}
	{
		int parentRenderOrderIndex = BaseWidget::GetRenderOrderIndex();

		m_backSprite = Nz::Sprite::New();
		Nz::MaterialRef mat = Nz::Material::New("Translucent2D");
		mat->GetDiffuseSampler().SetAnisotropyLevel(10);
		m_backSprite->SetMaterial(mat);
		m_backEntity = CreateEntity();
		m_backEntity->AddComponent<NodeComponent>().SetParent(this);
		m_backEntity->AddComponent<GraphicsComponent>().Attach(m_backSprite, parentRenderOrderIndex + 1);

		m_centerButtonSprite = Nz::SlicedSprite::New();
		mat = Nz::Material::New("Translucent2D");
		mat->GetDiffuseSampler().SetAnisotropyLevel(10);
		m_centerButtonSprite->SetMaterial(mat);
		m_centerButtonEntity = CreateEntity();
		m_centerButtonEntity->AddComponent<NodeComponent>().SetParent(this);
		m_centerButtonEntity->AddComponent<GraphicsComponent>().Attach(m_centerButtonSprite, parentRenderOrderIndex + 2);

		m_moreButtonSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_moreButtonEntity = CreateEntity();
		m_moreButtonEntity->AddComponent<NodeComponent>().SetParent(this);
		m_moreButtonEntity->AddComponent<GraphicsComponent>().Attach(m_moreButtonSprite, parentRenderOrderIndex + 1);

		m_lessButtonSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_lessButtonEntity = CreateEntity();
		m_lessButtonEntity->AddComponent<NodeComponent>().SetParent(this);
		m_lessButtonEntity->AddComponent<GraphicsComponent>().Attach(m_lessButtonSprite, parentRenderOrderIndex + 1);

		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollCenterName), ScrollBarButton_Center, ButtonState_Idle);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollCenterHoveredName), ScrollBarButton_Center, ButtonState_Hovered);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollCenterPressedName), ScrollBarButton_Center, ButtonState_Pressed);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollCenterDisabledName), ScrollBarButton_Center, ButtonState_Disabled);

		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollLeftName), ScrollBarButton_Left, ButtonState_Idle);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollLeftHoveredName), ScrollBarButton_Left, ButtonState_Hovered);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollLeftPressedName), ScrollBarButton_Left, ButtonState_Pressed);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollLeftDisabledName), ScrollBarButton_Left, ButtonState_Disabled);

		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollRightName), ScrollBarButton_Right, ButtonState_Idle);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollRightHoveredName), ScrollBarButton_Right, ButtonState_Hovered);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollRightPressedName), ScrollBarButton_Right, ButtonState_Pressed);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollRightDisabledName), ScrollBarButton_Right, ButtonState_Disabled);

		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollUpName), ScrollBarButton_Up, ButtonState_Idle);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollUpHoveredName), ScrollBarButton_Up, ButtonState_Hovered);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollUpPressedName), ScrollBarButton_Up, ButtonState_Pressed);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollUpDisabledName), ScrollBarButton_Up, ButtonState_Disabled);

		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollDownName), ScrollBarButton_Down, ButtonState_Idle);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollDownHoveredName), ScrollBarButton_Down, ButtonState_Hovered);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollDownPressedName), ScrollBarButton_Down, ButtonState_Pressed);
		SetButtonTexture(Nz::TextureLibrary::Get(s_scrollDownDisabledName), ScrollBarButton_Down, ButtonState_Disabled);

		SetCenterButtonSliceMargin(16.f / GetButtonTexture(ScrollBarButton_Center, ButtonState_Idle)->GetWidth());

		SetBackgroundTexture(Nz::TextureLibrary::Get(s_scrollBackgroundHorizontalName), SliderOrientation_Horizontal);
		SetBackgroundTexture(Nz::TextureLibrary::Get(s_scrollBackgroundVerticalName), SliderOrientation_Vertical);

		UpdatePreferedSize();
	}

	bool SimpleScrollBarWidget::Initialize()
	{
		const Nz::UInt8 r_center[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarCenter.png.h>
		};

		const Nz::UInt8 r_centerHovered[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarCenterHovered.png.h>
		};

		const Nz::UInt8 r_centerPressed[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarCenterPressed.png.h>
		};

		const Nz::UInt8 r_centerDisabled[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarCenterDisabled.png.h>
		};

		const Nz::UInt8 r_backHorizontal[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarBackgroundHorizontal.png.h>
		};

		const Nz::UInt8 r_backVertical[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarBackgroundVertical.png.h>
		};

		const Nz::UInt8 r_left[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowLeft.png.h>
		};

		const Nz::UInt8 r_leftHovered[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowLeftHovered.png.h>
		};

		const Nz::UInt8 r_leftPressed[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowLeftPressed.png.h>
		};

		const Nz::UInt8 r_leftDisabled[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowLeftDisabled.png.h>
		};

		const Nz::UInt8 r_right[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowRight.png.h>
		};

		const Nz::UInt8 r_rightHovered[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowRightHovered.png.h>
		};

		const Nz::UInt8 r_rightPressed[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowRightPressed.png.h>
		};

		const Nz::UInt8 r_rightDisabled[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowRightDisabled.png.h>
		};

		const Nz::UInt8 r_up[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowUp.png.h>
		};

		const Nz::UInt8 r_upHovered[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowUpHovered.png.h>
		};

		const Nz::UInt8 r_upPressed[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowUpPressed.png.h>
		};

		const Nz::UInt8 r_upDisabled[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowUpDisabled.png.h>
		};

		const Nz::UInt8 r_down[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowDown.png.h>
		};

		const Nz::UInt8 r_downHovered[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowDownHovered.png.h>
		};

		const Nz::UInt8 r_downPressed[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowDownPressed.png.h>
		};

		const Nz::UInt8 r_downDisabled[] =
		{
			#include <NDK/Resources/Widgets/ScrollbarArrowDownDisabled.png.h>
		};

		Nz::TextureRef centerTexture = Nz::Texture::LoadFromMemory(r_center, sizeof(r_center) / sizeof(r_center[0]));
		if (!centerTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarCenter.png");
			return false;
		}

		Nz::TextureRef centerHoveredTexture = Nz::Texture::LoadFromMemory(r_centerHovered, sizeof(r_centerHovered) / sizeof(r_centerHovered[0]));
		if (!centerHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarCenterHovered.png");
			return false;
		}

		Nz::TextureRef centerPressedTexture = Nz::Texture::LoadFromMemory(r_centerPressed, sizeof(r_centerPressed) / sizeof(r_centerPressed[0]));
		if (!centerHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarCenterPressed.png");
			return false;
		}

		Nz::TextureRef centerDisabledTexture = Nz::Texture::LoadFromMemory(r_centerDisabled, sizeof(r_centerDisabled) / sizeof(r_centerDisabled[0]));
		if (!centerDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarCenterDisabled.png");
			return false;
		}

		Nz::TextureRef backHorizontalTexture = Nz::Texture::LoadFromMemory(r_backHorizontal, sizeof(r_backHorizontal) / sizeof(r_backHorizontal[0]));
		if (!backHorizontalTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarBackgroundHorizontal.png");
			return false;
		}

		Nz::TextureRef backVerticalTexture = Nz::Texture::LoadFromMemory(r_backVertical, sizeof(r_backVertical) / sizeof(r_backVertical[0]));
		if (!backVerticalTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarBackgroundVertical.png");
			return false;
		}

		Nz::TextureRef leftTexture = Nz::Texture::LoadFromMemory(r_left, sizeof(r_left) / sizeof(r_left[0]));
		if (!leftTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowLeft.png");
			return false;
		}

		Nz::TextureRef leftHoveredTexture = Nz::Texture::LoadFromMemory(r_leftHovered, sizeof(r_leftHovered) / sizeof(r_leftHovered[0]));
		if (!leftHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowLeftHovered.png");
			return false;
		}

		Nz::TextureRef leftPressedTexture = Nz::Texture::LoadFromMemory(r_leftPressed, sizeof(r_leftPressed) / sizeof(r_leftPressed[0]));
		if (!leftPressedTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowLeftPressed.png");
			return false;
		}

		Nz::TextureRef leftDisabledTexture = Nz::Texture::LoadFromMemory(r_leftDisabled, sizeof(r_leftDisabled) / sizeof(r_leftDisabled[0]));
		if (!leftDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowLeftDisabled.png");
			return false;
		}

		Nz::TextureRef rightTexture = Nz::Texture::LoadFromMemory(r_right, sizeof(r_right) / sizeof(r_right[0]));
		if (!rightTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowRight.png");
			return false;
		}

		Nz::TextureRef rightHoveredTexture = Nz::Texture::LoadFromMemory(r_rightHovered, sizeof(r_rightHovered) / sizeof(r_rightHovered[0]));
		if (!rightHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowRightHovered.png");
			return false;
		}

		Nz::TextureRef rightPressedTexture = Nz::Texture::LoadFromMemory(r_rightPressed, sizeof(r_rightPressed) / sizeof(r_rightPressed[0]));
		if (!rightPressedTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowRightPressed.png");
			return false;
		}

		Nz::TextureRef rightDisabledTexture = Nz::Texture::LoadFromMemory(r_rightDisabled, sizeof(r_rightDisabled) / sizeof(r_rightDisabled[0]));
		if (!rightDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowRightDisabled.png");
			return false;
		}

		Nz::TextureRef upTexture = Nz::Texture::LoadFromMemory(r_up, sizeof(r_up) / sizeof(r_up[0]));
		if (!upTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowUp.png");
			return false;
		}

		Nz::TextureRef upHoveredTexture = Nz::Texture::LoadFromMemory(r_upHovered, sizeof(r_upHovered) / sizeof(r_upHovered[0]));
		if (!upHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowUpHovered.png");
			return false;
		}

		Nz::TextureRef upPressedTexture = Nz::Texture::LoadFromMemory(r_upPressed, sizeof(r_upPressed) / sizeof(r_upPressed[0]));
		if (!upPressedTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowUpPressed.png");
			return false;
		}

		Nz::TextureRef upDisabledTexture = Nz::Texture::LoadFromMemory(r_upDisabled, sizeof(r_upDisabled) / sizeof(r_upDisabled[0]));
		if (!upDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowUpDisabled.png");
			return false;
		}

		Nz::TextureRef downTexture = Nz::Texture::LoadFromMemory(r_down, sizeof(r_down) / sizeof(r_down[0]));
		if (!downTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowDown.png");
			return false;
		}

		Nz::TextureRef downHoveredTexture = Nz::Texture::LoadFromMemory(r_downHovered, sizeof(r_downHovered) / sizeof(r_downHovered[0]));
		if (!downHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowDownHovered.png");
			return false;
		}

		Nz::TextureRef downPressedTexture = Nz::Texture::LoadFromMemory(r_downPressed, sizeof(r_downPressed) / sizeof(r_downPressed[0]));
		if (!downPressedTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowDownPressed.png");
			return false;
		}

		Nz::TextureRef downDisabledTexture = Nz::Texture::LoadFromMemory(r_downDisabled, sizeof(r_downDisabled) / sizeof(r_downDisabled[0]));
		if (!downDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/ScrollbarArrowDownDisabled.png");
			return false;
		}

		Nz::TextureLibrary::Register(s_scrollCenterName, std::move(centerTexture));
		Nz::TextureLibrary::Register(s_scrollCenterHoveredName, std::move(centerHoveredTexture));
		Nz::TextureLibrary::Register(s_scrollCenterPressedName, std::move(centerPressedTexture));
		Nz::TextureLibrary::Register(s_scrollCenterDisabledName, std::move(centerDisabledTexture));
		Nz::TextureLibrary::Register(s_scrollBackgroundHorizontalName, std::move(backHorizontalTexture));
		Nz::TextureLibrary::Register(s_scrollBackgroundVerticalName, std::move(backVerticalTexture));
		Nz::TextureLibrary::Register(s_scrollLeftName, std::move(leftTexture));
		Nz::TextureLibrary::Register(s_scrollLeftHoveredName, std::move(leftHoveredTexture));
		Nz::TextureLibrary::Register(s_scrollLeftPressedName, std::move(leftPressedTexture));
		Nz::TextureLibrary::Register(s_scrollLeftDisabledName, std::move(leftDisabledTexture));
		Nz::TextureLibrary::Register(s_scrollRightName, std::move(rightTexture));
		Nz::TextureLibrary::Register(s_scrollRightHoveredName, std::move(rightHoveredTexture));
		Nz::TextureLibrary::Register(s_scrollRightPressedName, std::move(rightPressedTexture));
		Nz::TextureLibrary::Register(s_scrollRightDisabledName, std::move(rightDisabledTexture));
		Nz::TextureLibrary::Register(s_scrollUpName, std::move(upTexture));
		Nz::TextureLibrary::Register(s_scrollUpHoveredName, std::move(upHoveredTexture));
		Nz::TextureLibrary::Register(s_scrollUpPressedName, std::move(upPressedTexture));
		Nz::TextureLibrary::Register(s_scrollUpDisabledName, std::move(upDisabledTexture));
		Nz::TextureLibrary::Register(s_scrollDownName, std::move(downTexture));
		Nz::TextureLibrary::Register(s_scrollDownHoveredName, std::move(downHoveredTexture));
		Nz::TextureLibrary::Register(s_scrollDownPressedName, std::move(downPressedTexture));
		Nz::TextureLibrary::Register(s_scrollDownDisabledName, std::move(downDisabledTexture));

		return true;
	}

	void SimpleScrollBarWidget::Uninitialize()
	{
		Nz::TextureLibrary::Unregister(s_scrollCenterName);
		Nz::TextureLibrary::Unregister(s_scrollCenterHoveredName);
		Nz::TextureLibrary::Unregister(s_scrollCenterPressedName);
		Nz::TextureLibrary::Unregister(s_scrollCenterDisabledName);
		Nz::TextureLibrary::Unregister(s_scrollBackgroundHorizontalName);
		Nz::TextureLibrary::Unregister(s_scrollBackgroundVerticalName);
		Nz::TextureLibrary::Unregister(s_scrollLeftName);
		Nz::TextureLibrary::Unregister(s_scrollLeftHoveredName);
		Nz::TextureLibrary::Unregister(s_scrollLeftPressedName);
		Nz::TextureLibrary::Unregister(s_scrollLeftDisabledName);
		Nz::TextureLibrary::Unregister(s_scrollRightName);
		Nz::TextureLibrary::Unregister(s_scrollRightHoveredName);
		Nz::TextureLibrary::Unregister(s_scrollRightPressedName);
		Nz::TextureLibrary::Unregister(s_scrollRightDisabledName);
		Nz::TextureLibrary::Unregister(s_scrollUpName);
		Nz::TextureLibrary::Unregister(s_scrollUpHoveredName);
		Nz::TextureLibrary::Unregister(s_scrollUpPressedName);
		Nz::TextureLibrary::Unregister(s_scrollUpDisabledName);
		Nz::TextureLibrary::Unregister(s_scrollDownName);
		Nz::TextureLibrary::Unregister(s_scrollDownHoveredName);
		Nz::TextureLibrary::Unregister(s_scrollDownPressedName);
		Nz::TextureLibrary::Unregister(s_scrollDownDisabledName);
	}

	int SimpleScrollBarWidget::GetRenderOrderIndex() const
	{
		//more and less buttons, background and slider

		return BaseSliderWidget::GetRenderOrderIndex() + 4;
	}

	void SimpleScrollBarWidget::Layout()
	{
		BaseSliderWidget::Layout();

		Nz::Vector2f size = GetSize();

		SliderOrientation orientation = GetOrientation();

		ButtonState moreState = GetCurrentStateMoreButton();
		ButtonState lessState = GetCurrentStateLessButton();
		ButtonState centerState = GetCurrentStateCenterButton();

		ScrollBarButton moreButton = orientation == SliderOrientation_Horizontal ? ScrollBarButton_Right : ScrollBarButton_Down;
		ScrollBarButton lessButton = orientation == SliderOrientation_Horizontal ? ScrollBarButton_Left : ScrollBarButton_Up;

		TextureInfo & moreTexture = m_buttonsDatas[moreButton][moreState];
		TextureInfo & lessTexture = m_buttonsDatas[lessButton][lessState];
		TextureInfo & centerTexture = m_buttonsDatas[ScrollBarButton_Center][centerState];
		TextureInfo & backgroundTexture = orientation == SliderOrientation_Horizontal ? m_horizontalBackgroundDatas : m_verticalBackgroundDatas;

		Nz::Rectf moreButtonRect = GetMoreButtonBounds();
		Nz::Rectf lessButtonRect = GetLessButtonBounds();
		Nz::Rectf centerButtonRect = GetCenterButtonBounds();
		Nz::Rectf sliderRect = GetSliderBounds();

		m_moreButtonSprite->SetTexture(moreTexture.texture, false);
		m_moreButtonSprite->SetTextureCoords(moreTexture.textureCoords);
		m_moreButtonSprite->SetColor(moreTexture.color);
		m_moreButtonSprite->SetSize(moreButtonRect.width, moreButtonRect.height);
		m_moreButtonEntity->GetComponent<NodeComponent>().SetPosition(moreButtonRect.x, moreButtonRect.y);

		m_lessButtonSprite->SetTexture(lessTexture.texture, false);
		m_lessButtonSprite->SetTextureCoords(lessTexture.textureCoords);
		m_lessButtonSprite->SetColor(lessTexture.color);
		m_lessButtonSprite->SetSize(lessButtonRect.width, lessButtonRect.height);
		m_lessButtonEntity->GetComponent<NodeComponent>().SetPosition(lessButtonRect.x, lessButtonRect.y);

		m_centerButtonSprite->SetTexture(centerTexture.texture, false);
		m_centerButtonSprite->SetTextureCoords(centerTexture.textureCoords);
		m_centerButtonSprite->SetColor(centerTexture.color);
		m_centerButtonSprite->SetSize(centerButtonRect.width, centerButtonRect.height);
		m_centerButtonEntity->GetComponent<NodeComponent>().SetPosition(centerButtonRect.x, centerButtonRect.y);

		m_backSprite->SetTexture(backgroundTexture.texture);
		m_backSprite->SetTextureCoords(backgroundTexture.textureCoords);
		m_backSprite->SetColor(backgroundTexture.color);
		m_backSprite->SetSize(sliderRect.width, sliderRect.height);
		m_backEntity->GetComponent<NodeComponent>().SetPosition(sliderRect.x, sliderRect.y);
	}

	void SimpleScrollBarWidget::UpdatePreferedSize()
	{
		SliderOrientation orientation = GetOrientation();

		ScrollBarButton moreButton = orientation == SliderOrientation_Horizontal ? ScrollBarButton_Up : ScrollBarButton_Left;
		ScrollBarButton lessButton = orientation == SliderOrientation_Horizontal ? ScrollBarButton_Down : ScrollBarButton_Right;

		TextureInfo & moreTexture = m_buttonsDatas[moreButton][ButtonState_Idle];
		TextureInfo & lessTexture = m_buttonsDatas[lessButton][ButtonState_Idle];

		Nz::Vector2f size(0, 0);
		if (moreTexture.texture.IsValid())
		{
			size.x = moreTexture.texture->GetWidth() * moreTexture.textureCoords.width;
			size.y = moreTexture.texture->GetHeight() * moreTexture.textureCoords.height;
		}

		if (lessTexture.texture.IsValid())
		{
			if (orientation == SliderOrientation_Horizontal)
			{
				size.x += lessTexture.texture->GetWidth() * lessTexture.textureCoords.width;
				size.y = std::max(size.y, lessTexture.texture->GetHeight() * lessTexture.textureCoords.height);
			}
			else
			{
				size.x = std::max(size.x, lessTexture.texture->GetWidth() * lessTexture.textureCoords.width);
				size.y += lessTexture.texture->GetHeight() * lessTexture.textureCoords.height;
			}
		}

		if (orientation == SliderOrientation_Horizontal)
			size.x *= 3;
		else size.y *= 3;

		SetPreferredSize(size);
	}

	void SimpleScrollBarWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{
		Nz::Rectf moreButtonRect = GetMoreButtonBounds();
		Nz::Rectf lessButtonRect = GetLessButtonBounds();
		Nz::Rectf centerButtonRect = GetCenterButtonBounds();
		Nz::Rectf sliderRect = GetSliderBounds();
		SliderOrientation orientation = GetOrientation();

		bool oldHovered = IsHovered();
		bool oldMoreHovered = IsButtonMoreHovered();
		bool oldLessHovered = IsButtonLessHovered();
		SetHovered(centerButtonRect.Contains(static_cast<float>(x), static_cast<float>(y)));
		SetButtonMoreHovered(moreButtonRect.Contains(static_cast<float>(x), static_cast<float>(y)));
		SetButtonLessHovered(lessButtonRect.Contains(static_cast<float>(x), static_cast<float>(y)));

		if (!IsButtonMoreHovered())
			SetButtonMorePressed(false);
		if (!IsButtonLessHovered())
			SetButtonLessPressed(false);
		if (!sliderRect.Contains(static_cast<float>(x), static_cast<float>(y)))
		{
			SetPressed(false);
			SetBackgroundPressed(false);
		}

		if (oldHovered != IsHovered() || oldMoreHovered != IsButtonMoreHovered() || oldLessHovered != IsButtonLessHovered())
			Layout();

		if (m_currentPressedButton == PressedButton_Center)
		{
			float normalizedValue = 0;
			if (orientation == SliderOrientation_Horizontal)
				normalizedValue = (x - m_pressOffset - sliderRect.x) / (sliderRect.width);
			else normalizedValue = (y - m_pressOffset - sliderRect.y) / (sliderRect.height);

			SetNormalizedValue(normalizedValue);
		}
		else
		{
			if (orientation == SliderOrientation_Horizontal)
				m_pressOffset = x - centerButtonRect.x - centerButtonRect.width / 2;
			else m_pressOffset = y - centerButtonRect.y - centerButtonRect.height / 2;
		}
	}

	void SimpleScrollBarWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{
		Nz::Rectf moreButtonRect = GetMoreButtonBounds();
		Nz::Rectf lessButtonRect = GetLessButtonBounds();
		Nz::Rectf centerButtonRect = GetCenterButtonBounds();
		Nz::Rectf sliderRect = GetSliderBounds();

		SetPressed(centerButtonRect.Contains(static_cast<float>(x), static_cast<float>(y)));
		SetButtonMorePressed(moreButtonRect.Contains(static_cast<float>(x), static_cast<float>(y)));
		SetButtonLessPressed(lessButtonRect.Contains(static_cast<float>(x), static_cast<float>(y)));
		SetBackgroundPressed(sliderRect.Contains(static_cast<float>(x), static_cast<float>(y)) && !IsPressed());

		if (m_currentPressedButton == PressedButton_Center)
		{
			if (GetOrientation() == SliderOrientation_Horizontal)
				m_pressOffset = x - centerButtonRect.x;
			else m_pressOffset = y - centerButtonRect.y;
		}

		if (m_currentPressedButton == PressedButton_Background)
		{
			if (GetOrientation() == SliderOrientation_Horizontal)
				m_pressOffset = x - centerButtonRect.x - centerButtonRect.width / 2;
			else m_pressOffset = y - centerButtonRect.y - centerButtonRect.height / 2;
		}

		Layout();
	}

	void SimpleScrollBarWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{
		SetPressed(false);
		SetBackgroundPressed(false);
		SetButtonMorePressed(false);
		SetButtonLessPressed(false);
		m_currentPressedButton = PressedButton_None;

		Layout();
	}

	void SimpleScrollBarWidget::OnMouseExit()
	{
		SetHovered(false);
		SetButtonMoreHovered(false);
		SetButtonLessHovered(false);

		SetPressed(false);
		SetBackgroundPressed(false);
		SetButtonMorePressed(false);
		SetButtonLessPressed(false);
		m_currentPressedButton = PressedButton_None;

		Layout();
	}

	void SimpleScrollBarWidget::Update(float elapsedTime)
	{
		if (m_currentPressedButton == PressedButton_Background)
		{
			float distance = elapsedTime * m_moveSpeed;
			if (distance > std::abs(m_pressOffset))
				distance = m_pressOffset;
			else if (m_pressOffset < 0)
				distance *= -1;

			Nz::Rectf sliderRect = GetSliderBounds();
			Nz::Rectf buttonRect = GetCenterButtonBounds();

			SliderOrientation orientation = GetOrientation();

			float value = 0;
			if (orientation == SliderOrientation_Horizontal)
				value = (buttonRect.x - sliderRect.x + distance) / (sliderRect.width);
			else value = (buttonRect.y - sliderRect.y + distance) / (sliderRect.height);

			m_pressOffset -= distance;

			if (orientation == SliderOrientation_Horizontal && std::abs(m_pressOffset) < buttonRect.width / 2.f)
				SetHovered(true);
			if (orientation == SliderOrientation_Vertical && std::abs(m_pressOffset) < buttonRect.height / 2.f)
				SetHovered(true);

			SetNormalizedValue(value);
		}
		else if (m_currentPressedButton == PressedButton_Less || m_currentPressedButton == PressedButton_More)
		{
			float offset = m_currentPressedButton == PressedButton_Less ? -1.f : 1.f;

			float value = GetValue();
			value += offset * m_moveButtonSpeed * elapsedTime;

			SetValue(value);
		}
		
	}

	ButtonState SimpleScrollBarWidget::GetCurrentStateMoreButton() const
	{
		if (!IsEnabled())
			return ButtonState_Disabled;
		if (m_buttonMorePressed)
			return ButtonState_Pressed;
		if (m_buttonMoreHovered)
			return ButtonState_Hovered;
		return ButtonState_Idle;
	}

	ButtonState SimpleScrollBarWidget::GetCurrentStateLessButton() const
	{
		if (!IsEnabled())
			return ButtonState_Disabled;
		if (m_buttonLessPressed)
			return ButtonState_Pressed;
		if (m_buttonLessHovered)
			return ButtonState_Hovered;
		return ButtonState_Idle;
	}

	ButtonState SimpleScrollBarWidget::GetCurrentStateCenterButton() const
	{
		if (!IsEnabled())
			return ButtonState_Disabled;
		if (m_pressed)
			return ButtonState_Pressed;
		if (m_hovered)
			return ButtonState_Hovered;
		return ButtonState_Idle;
	}

	Nz::Rectf SimpleScrollBarWidget::GetSliderBounds() const
	{
		Nz::Vector2f size = GetSize();

		SliderOrientation orientation = GetOrientation();

		Nz::Rectf lessRect = GetLessButtonBounds();
		Nz::Rectf moreRect = GetMoreButtonBounds();

		Nz::Rectf rect(0, 0, size.x, size.y);

		if (orientation == SliderOrientation_Horizontal)
		{
			rect.x = lessRect.x + lessRect.width;
			rect.width = moreRect.x - rect.x;
		}
		else
		{
			rect.y = lessRect.y + lessRect.height;
			rect.height = moreRect.y - rect.y;
		}

		return rect;
	}

	Nz::Rectf SimpleScrollBarWidget::GetCenterButtonBounds() const
	{
		Nz::Rectf rect = GetSliderBounds();

		SliderOrientation orientation = GetOrientation();

		float value = GetNormalizedValue();
		float size = GetNormalizedValueSize();

		if (orientation == SliderOrientation_Horizontal)
		{
			rect.x += rect.width * value;
			rect.width *= size;
		}
		else
		{
			rect.y += rect.height * value;
			rect.height *= size;
		}

		return rect;
	}

	Nz::Rectf SimpleScrollBarWidget::GetLessButtonBounds() const
	{
		Nz::Vector2f size = GetSize();
		SliderOrientation orientation = GetOrientation();

		ScrollBarButton button = orientation == SliderOrientation_Horizontal ? ScrollBarButton_Left : ScrollBarButton_Up;
		const TextureInfo& buttonInfo = m_buttonsDatas[button][GetCurrentStateLessButton()];

		if (!buttonInfo.texture.IsValid())
			return Nz::Rectf(0, 0, 0, 0);

		Nz::Vector2f buttonSize(buttonInfo.texture->GetWidth() * buttonInfo.textureCoords.width, buttonInfo.texture->GetHeight() * buttonInfo.textureCoords.height);

		Nz::Rectf rect(0, 0, size.x, size.y);

		if (orientation == SliderOrientation_Horizontal)
			rect.width = buttonSize.x * size.y / buttonSize.y;
		else rect.height = buttonSize.y * size.x / buttonSize.x;

		return rect;
	}

	Nz::Rectf SimpleScrollBarWidget::GetMoreButtonBounds() const
	{
		Nz::Vector2f size = GetSize();
		SliderOrientation orientation = GetOrientation();

		ScrollBarButton button = orientation == SliderOrientation_Horizontal ? ScrollBarButton_Right : ScrollBarButton_Down;
		const TextureInfo& buttonInfo = m_buttonsDatas[button][GetCurrentStateMoreButton()];

		if (!buttonInfo.texture.IsValid())
			return Nz::Rectf(size.x, size.y, 0, 0);

		Nz::Vector2f buttonSize(buttonInfo.texture->GetWidth() * buttonInfo.textureCoords.width, buttonInfo.texture->GetHeight() * buttonInfo.textureCoords.height);

		Nz::Rectf rect(0, 0, size.x, size.y);

		if (orientation == SliderOrientation_Horizontal)
			rect.width = buttonSize.x * size.y / buttonSize.y;
		else rect.height = buttonSize.y * size.x / buttonSize.x;

		rect.x = size.x - rect.width;
		rect.y = size.y - rect.height;

		return rect;
	}
}
