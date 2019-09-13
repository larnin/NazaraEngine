#include <NDK/Widgets/Simple/SimpleSliderWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>

namespace Ndk
{
	const std::string SimpleSliderWidget::s_sliderBackHorizontalName("Ndk::Slider::horizontalBack");
	const std::string SimpleSliderWidget::s_sliderBackHorizontalDisabledName("Ndk::Slider::horizontalBackDisabled");
	const std::string SimpleSliderWidget::s_sliderHorizontalName("Ndk::Slider::horizontalIdle");
	const std::string SimpleSliderWidget::s_sliderHorizontalHoveredName("Ndk::Slider::horizontalHovered");
	const std::string SimpleSliderWidget::s_sliderHorizontalPressedName("Ndk::Slider::horizontalPressed");
	const std::string SimpleSliderWidget::s_sliderHorizontalDisabledName("Ndk::Slider::horizontalDisabled");
	const std::string SimpleSliderWidget::s_sliderBackVerticalName("Ndk::Slider::verticalBack");
	const std::string SimpleSliderWidget::s_sliderBackVerticalDisabledName("Ndk::Slider::verticalBackDisabled");
	const std::string SimpleSliderWidget::s_sliderVerticalName("Ndk::Slider::verticalIdle");
	const std::string SimpleSliderWidget::s_sliderVerticalHoveredName("Ndk::Slider::verticalHovered");
	const std::string SimpleSliderWidget::s_sliderVerticalPressedName("Ndk::Slider::verticalPressed");
	const std::string SimpleSliderWidget::s_sliderVerticalDisabledName("Ndk::Slider::verticalDisabled");

	SimpleSliderWidget::TextureInfo::TextureInfo() :
	color{ 255, 255, 255 },
	textureCoords{ 0.f, 0.f, 1.f, 1.f }
	{

	}

	SimpleSliderWidget::SimpleSliderWidget(BaseWidget* parent) :
	BaseSliderWidget(parent),
	m_hovered{false},
	m_pressed{false},
	m_backMargin{0}
	{
		int parentRenderOrderIndex = BaseWidget::GetRenderOrderIndex();

		m_backSprite = Nz::SlicedSprite::New();
		Nz::MaterialRef mat = Nz::Material::New("Translucent2D");
		mat->GetDiffuseSampler().SetAnisotropyLevel(10);
		m_backSprite->SetMaterial(mat);

		m_backEntity = CreateEntity();
		m_backEntity->AddComponent<NodeComponent>().SetParent(this);
		m_backEntity->AddComponent<GraphicsComponent>().Attach(m_backSprite, parentRenderOrderIndex + 1);

		m_sliderSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));

		m_sliderEntity = CreateEntity();
		m_sliderEntity->AddComponent<NodeComponent>().SetParent(this);
		m_sliderEntity->AddComponent<GraphicsComponent>().Attach(m_sliderSprite, parentRenderOrderIndex + 2);

		//add text

		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderHorizontalName), SliderOrientation_Horizontal, ButtonState_Idle);
		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderHorizontalHoveredName), SliderOrientation_Horizontal, ButtonState_Hovered);
		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderHorizontalDisabledName), SliderOrientation_Horizontal, ButtonState_Pressed);
		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderHorizontalDisabledName), SliderOrientation_Horizontal, ButtonState_Disabled);

		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderVerticalName), SliderOrientation_Vertical, ButtonState_Idle);
		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderVerticalHoveredName), SliderOrientation_Vertical, ButtonState_Hovered);
		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderVerticalPressedName), SliderOrientation_Vertical, ButtonState_Pressed);
		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderVerticalDisabledName), SliderOrientation_Vertical, ButtonState_Disabled);

		SetBackgroundTexture(Nz::TextureLibrary::Get(s_sliderBackHorizontalName), SliderOrientation_Horizontal, false);
		SetBackgroundTexture(Nz::TextureLibrary::Get(s_sliderBackHorizontalDisabledName), SliderOrientation_Horizontal, true);
		SetBackgroundTexture(Nz::TextureLibrary::Get(s_sliderBackVerticalName), SliderOrientation_Vertical, false);
		SetBackgroundTexture(Nz::TextureLibrary::Get(s_sliderBackVerticalDisabledName), SliderOrientation_Vertical, true);

		SetBackgroundMargin(8.f / GetBackgroundTexture(SliderOrientation_Horizontal, false)->GetWidth());

		Layout();
	}

	bool SimpleSliderWidget::Initialize()
	{
		const Nz::UInt8 r_horizontalBack[] =
		{
			#include <NDK/Resources/Widgets/SliderBackHorizontal.png.h>
		};

		const Nz::UInt8 r_horizontalBackDisabled[] =
		{
			#include <NDK/Resources/Widgets/SliderBackHorizontalDisabled.png.h>
		};

		const Nz::UInt8 r_horizontalIdle[] =
		{
			#include <NDK/Resources/Widgets/SliderHorizontal.png.h>
		};

		const Nz::UInt8 r_horizontalHovered[] =
		{
			#include <NDK/Resources/Widgets/SliderHorizontalHovered.png.h>
		};

		const Nz::UInt8 r_horizontalPressed[] =
		{
			#include <NDK/Resources/Widgets/SliderHorizontalPressed.png.h>
		};

		const Nz::UInt8 r_horizontalDisabled[] =
		{
			#include <NDK/Resources/Widgets/SliderHorizontalDisabled.png.h>
		};

		const Nz::UInt8 r_verticalBack[] =
		{
			#include <NDK/Resources/Widgets/SliderBackVertical.png.h>
		};

		const Nz::UInt8 r_verticalBackDisabled[] =
		{
			#include <NDK/Resources/Widgets/SliderBackVerticalDisabled.png.h>
		};

		const Nz::UInt8 r_verticalIdle[] =
		{
			#include <NDK/Resources/Widgets/SliderVertical.png.h>
		};

		const Nz::UInt8 r_verticalHovered[] =
		{
			#include <NDK/Resources/Widgets/SliderVerticalHovered.png.h>
		};

		const Nz::UInt8 r_verticalPressed[] =
		{
			#include <NDK/Resources/Widgets/SliderVerticalPressed.png.h>
		};

		const Nz::UInt8 r_verticalDisabled[] =
		{
			#include <NDK/Resources/Widgets/SliderVerticalDisabled.png.h>
		};

		Nz::TextureRef horizontalBackTexture = Nz::Texture::LoadFromMemory(r_horizontalBack, sizeof(r_horizontalBack) / sizeof(r_horizontalBack[0]));
		if (!horizontalBackTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderBackHorizontal.png");
			return false;
		}

		Nz::TextureRef horizontalBackDisabledTexture = Nz::Texture::LoadFromMemory(r_horizontalBackDisabled, sizeof(r_horizontalBackDisabled) / sizeof(r_horizontalBackDisabled[0]));
		if (!horizontalBackDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderBackHorizontalDisabled.png");
			return false;
		}

		Nz::TextureRef horizontalIdleTexture = Nz::Texture::LoadFromMemory(r_horizontalIdle, sizeof(r_horizontalIdle) / sizeof(r_horizontalIdle[0]));
		if (!horizontalIdleTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderHorizontal.png");
			return false;
		}

		Nz::TextureRef horizontalHoveredTexture = Nz::Texture::LoadFromMemory(r_horizontalHovered, sizeof(r_horizontalHovered) / sizeof(r_horizontalHovered[0]));
		if (!horizontalHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderHorizontalHovered.png");
			return false;
		}

		Nz::TextureRef horizontalPressedTexture = Nz::Texture::LoadFromMemory(r_horizontalPressed, sizeof(r_horizontalPressed) / sizeof(r_horizontalPressed[0]));
		if (!horizontalPressedTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderHorizontalPressed.png");
			return false;
		}

		Nz::TextureRef horizontalDisabledTexture = Nz::Texture::LoadFromMemory(r_horizontalDisabled, sizeof(r_horizontalDisabled) / sizeof(r_horizontalDisabled[0]));
		if (!horizontalDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderHorizontalDisabled.png");
			return false;
		}

		Nz::TextureRef verticalBackTexture = Nz::Texture::LoadFromMemory(r_verticalBack, sizeof(r_verticalBack) / sizeof(r_verticalBack[0]));
		if (!horizontalBackTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderBackVertical.png");
			return false;
		}

		Nz::TextureRef verticalBackDisabledTexture = Nz::Texture::LoadFromMemory(r_verticalBackDisabled, sizeof(r_verticalBackDisabled) / sizeof(r_verticalBackDisabled[0]));
		if (!horizontalBackDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderBackVerticalDisabled.png");
			return false;
		}

		Nz::TextureRef verticalIdleTexture = Nz::Texture::LoadFromMemory(r_verticalIdle, sizeof(r_verticalIdle) / sizeof(r_verticalIdle[0]));
		if (!verticalIdleTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderVertical.png");
			return false;
		}

		Nz::TextureRef verticalHoveredTexture = Nz::Texture::LoadFromMemory(r_verticalHovered, sizeof(r_verticalHovered) / sizeof(r_verticalHovered[0]));
		if (!verticalHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderVerticalHovered.png");
			return false;
		}

		Nz::TextureRef verticalPressedTexture = Nz::Texture::LoadFromMemory(r_verticalPressed, sizeof(r_verticalPressed) / sizeof(r_verticalPressed[0]));
		if (!verticalPressedTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderVerticalPressed.png");
			return false;
		}

		Nz::TextureRef verticalDisabledTexture = Nz::Texture::LoadFromMemory(r_verticalDisabled, sizeof(r_verticalDisabled) / sizeof(r_verticalDisabled[0]));
		if (!verticalDisabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/SliderVerticalDisabled.png");
			return false;
		}

		Nz::TextureLibrary::Register(s_sliderBackHorizontalName, std::move(horizontalBackTexture));
		Nz::TextureLibrary::Register(s_sliderBackHorizontalDisabledName, std::move(horizontalBackDisabledTexture));
		Nz::TextureLibrary::Register(s_sliderHorizontalName, std::move(horizontalIdleTexture));
		Nz::TextureLibrary::Register(s_sliderHorizontalHoveredName, std::move(horizontalHoveredTexture));
		Nz::TextureLibrary::Register(s_sliderHorizontalPressedName, std::move(horizontalPressedTexture));
		Nz::TextureLibrary::Register(s_sliderHorizontalDisabledName, std::move(horizontalDisabledTexture));
		Nz::TextureLibrary::Register(s_sliderBackVerticalName, std::move(verticalBackTexture));
		Nz::TextureLibrary::Register(s_sliderBackVerticalDisabledName, std::move(verticalBackDisabledTexture));
		Nz::TextureLibrary::Register(s_sliderVerticalName, std::move(verticalIdleTexture));
		Nz::TextureLibrary::Register(s_sliderVerticalHoveredName, std::move(verticalHoveredTexture));
		Nz::TextureLibrary::Register(s_sliderVerticalPressedName, std::move(verticalPressedTexture));
		Nz::TextureLibrary::Register(s_sliderVerticalDisabledName, std::move(verticalDisabledTexture));

		return true;
	}

	void SimpleSliderWidget::Uninitialize()
	{
		Nz::TextureLibrary::Unregister(s_sliderBackHorizontalName);
		Nz::TextureLibrary::Unregister(s_sliderBackHorizontalDisabledName);
		Nz::TextureLibrary::Unregister(s_sliderHorizontalName);
		Nz::TextureLibrary::Unregister(s_sliderHorizontalHoveredName);
		Nz::TextureLibrary::Unregister(s_sliderHorizontalPressedName);
		Nz::TextureLibrary::Unregister(s_sliderHorizontalDisabledName);
		Nz::TextureLibrary::Unregister(s_sliderBackVerticalName);
		Nz::TextureLibrary::Unregister(s_sliderBackVerticalDisabledName);
		Nz::TextureLibrary::Unregister(s_sliderVerticalName);
		Nz::TextureLibrary::Unregister(s_sliderVerticalHoveredName);
		Nz::TextureLibrary::Unregister(s_sliderVerticalPressedName);
		Nz::TextureLibrary::Unregister(s_sliderVerticalDisabledName);
	}

	int SimpleSliderWidget::GetRenderOrderIndex() const
	{
		return BaseSliderWidget::GetRenderOrderIndex() + 3;
	}

	void SimpleSliderWidget::Layout()
	{
		BaseSliderWidget::Layout();

		Nz::Vector2f size = GetSize();
		ButtonState state = GetCurrentState();
		SliderOrientation orientation = GetOrientation();
		
		TextureInfo &infos = m_sliderDatas[orientation][state];
		TextureInfo & backInfos = IsEnabledInHierarchy() ? m_back[orientation] : m_backDisabled[orientation];

		Nz::Vector2f sliderSize(32, 32);
		Nz::Vector2f sliderRenderSize(size);
		float sliderValue = GetNormalizedValue();

		if (infos.texture.IsValid())
		{
			m_sliderSprite->SetTexture(infos.texture, false);
			m_sliderSprite->SetTextureCoords(infos.textureCoords);
			m_sliderSprite->SetColor(infos.color);
			m_sliderEntity->Enable(true);

			Nz::Vector2f pos(0, 0);

			sliderSize.x = infos.texture->GetWidth() * infos.textureCoords.width;
			sliderSize.y = infos.texture->GetHeight() * infos.textureCoords.height;

			if (orientation == SliderOrientation_Horizontal)
			{
				sliderRenderSize.y = size.y;
				sliderRenderSize.x = sliderRenderSize.y / sliderSize.y * sliderSize.x;
				pos.x = sliderValue * (size.x - sliderRenderSize.x);
			}
			else
			{
				sliderRenderSize.x = size.x;
				sliderRenderSize.y = sliderRenderSize.x / sliderSize.x * sliderSize.y;
				pos.y = sliderValue * (size.y - sliderRenderSize.y);
			}

			m_sliderSprite->SetSize(sliderRenderSize);
			m_sliderEntity->GetComponent<NodeComponent>().SetPosition(pos);
		}
		else m_sliderEntity->Enable(false);

		if (backInfos.texture.IsValid())
		{
			m_backSprite->SetTexture(backInfos.texture, false);
			m_backSprite->SetTextureCoords(backInfos.textureCoords);
			m_backSprite->SetColor(backInfos.color);
			m_backEntity->Enable(true);

			Nz::Vector2f pos(0, 0);
			Nz::Vector2f spriteSize(backInfos.texture->GetWidth() * backInfos.textureCoords.width, backInfos.texture->GetHeight() * backInfos.textureCoords.height);
			Nz::Vector2f margin(0, 0);
			if (orientation == SliderOrientation_Horizontal)
			{
				spriteSize.x = size.x - sliderRenderSize.x;
				spriteSize.y *= sliderRenderSize.y / sliderSize.y;
				pos.y = (size.y - spriteSize.y) / 2.f;
				pos.x = sliderRenderSize.x / 2.f;
				margin.x = GetBackgroundMargin();
			}
			else
			{
				spriteSize.y = size.y - sliderRenderSize.y;
				spriteSize.x *= sliderRenderSize.x / sliderSize.x;
				pos.x = (size.x - spriteSize.x) / 2.f;
				pos.y = sliderRenderSize.y / 2.f;
				margin.y = GetBackgroundMargin();
			}
			m_backEntity->GetComponent<NodeComponent>().SetPosition(pos);
			m_backSprite->SetSize(spriteSize);
			m_backSprite->SetSliceMargin(margin.y, margin.y, margin.x, margin.x);
		}
		else m_backEntity->Enable(false);
		
	}

	void SimpleSliderWidget::UpdatePreferedSize()
	{
		SliderOrientation orientation = GetOrientation();

		TextureInfo &infos = m_sliderDatas[orientation][ButtonState_Idle];

		Nz::Vector2f size(10, 10);
		if (infos.texture.IsValid())
		{
			size.x = infos.texture->GetWidth() * infos.textureCoords.width;
			size.y = infos.texture->GetHeight() * infos.textureCoords.height;
		}

		if (orientation == SliderOrientation_Horizontal)
			size.x *= 10;
		else size.y *= 10;

		//add text size here

		SetPreferredSize(size);
	}

	ButtonState SimpleSliderWidget::GetCurrentState() const
	{
		if (!IsEnabledInHierarchy())
			return ButtonState_Disabled;
		if (m_pressed)
			return ButtonState_Pressed;
		if (m_hovered)
			return ButtonState_Hovered;
		return ButtonState_Idle;
	}

	void SimpleSliderWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{

	}

	void SimpleSliderWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{

	}

	void SimpleSliderWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{

	}

	void SimpleSliderWidget::OnMouseExit()
	{

	}
}
