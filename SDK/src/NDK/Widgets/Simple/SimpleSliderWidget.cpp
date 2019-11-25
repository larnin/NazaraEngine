#include <NDK/Widgets/Simple/SimpleSliderWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <Nazara/Utility/SimpleTextDrawer.hpp>

#include <sstream>

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
	m_backgroundPressed{false},
	m_pressOffset{0},
	m_moveSpeed{250},
	m_backMargin{0},
	m_textEnabled{true},
	m_textCharacterSize{15},
	m_textStyle{Nz::TextStyle_Regular},
	m_textColor{Nz::Color::White},
	m_textPosition{ButtonTextAlignment_Right},
	m_textMargin{5},
	m_textPrecision{1},
	m_textMaxSize{0, 0},
	m_textSize{0, 0}
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

		m_textSprite = Nz::TextSprite::New();;

		m_textEntity = CreateEntity();
		m_textEntity->AddComponent<NodeComponent>().SetParent(this);
		m_textEntity->AddComponent<GraphicsComponent>().Attach(m_textSprite, parentRenderOrderIndex + 3);

		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderHorizontalName), SliderOrientation_Horizontal, ButtonState_Idle);
		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderHorizontalHoveredName), SliderOrientation_Horizontal, ButtonState_Hovered);
		SetSliderTexture(Nz::TextureLibrary::Get(s_sliderHorizontalPressedName), SliderOrientation_Horizontal, ButtonState_Pressed);
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

		UpdateTextSize();
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

		Nz::Vector2f sliderBaseSize = GetSliderSize();
		ButtonState state = GetCurrentState();
		SliderOrientation orientation = GetOrientation();
		
		TextureInfo &infos = m_sliderDatas[orientation][state];
		TextureInfo & backInfos = IsEnabled() ? m_back[orientation] : m_backDisabled[orientation];

		Nz::Vector2f sliderSize(32, 32);
		Nz::Vector2f sliderRenderSize(sliderBaseSize);
		float sliderValue = GetNormalizedValue();

		Nz::Vector2f sliderPos = GetSliderPos();

		bool isVisible = IsVisible();

		if (infos.texture.IsValid())
		{
			m_sliderSprite->SetTexture(infos.texture, false);
			m_sliderSprite->SetTextureCoords(infos.textureCoords);
			m_sliderSprite->SetColor(infos.color);
			m_sliderEntity->Enable(isVisible);

			Nz::Vector2f pos(0, 0);

			sliderSize.x = infos.texture->GetWidth() * infos.textureCoords.width;
			sliderSize.y = infos.texture->GetHeight() * infos.textureCoords.height;

			if (orientation == SliderOrientation_Horizontal)
			{
				sliderRenderSize.y = sliderBaseSize.y;
				sliderRenderSize.x = sliderRenderSize.y / sliderSize.y * sliderSize.x;
				pos.x = sliderValue * (sliderBaseSize.x - sliderRenderSize.x);
			}
			else
			{
				sliderRenderSize.x = sliderBaseSize.x;
				sliderRenderSize.y = sliderRenderSize.x / sliderSize.x * sliderSize.y;
				pos.y = sliderValue * (sliderBaseSize.y - sliderRenderSize.y);
			}

			m_sliderSprite->SetSize(sliderRenderSize);
			m_sliderEntity->GetComponent<NodeComponent>().SetPosition(pos + sliderPos);
		}
		else m_sliderEntity->Disable();

		if (backInfos.texture.IsValid())
		{
			m_backSprite->SetTexture(backInfos.texture, false);
			m_backSprite->SetTextureCoords(backInfos.textureCoords);
			m_backSprite->SetColor(backInfos.color);
			m_backEntity->Enable(isVisible);

			Nz::Vector2f pos(0, 0);
			Nz::Vector2f spriteSize(backInfos.texture->GetWidth() * backInfos.textureCoords.width, backInfos.texture->GetHeight() * backInfos.textureCoords.height);
			Nz::Vector2f margin(0, 0);
			if (orientation == SliderOrientation_Horizontal)
			{
				spriteSize.x = sliderBaseSize.x - sliderRenderSize.x;
				spriteSize.y *= sliderRenderSize.y / sliderSize.y;
				pos.y = (sliderBaseSize.y - spriteSize.y) / 2.f;
				pos.x = sliderRenderSize.x / 2.f;
				margin.x = GetBackgroundMargin();
			}
			else
			{
				spriteSize.y = sliderBaseSize.y - sliderRenderSize.y;
				spriteSize.x *= sliderRenderSize.x / sliderSize.x;
				pos.x = (sliderBaseSize.x - spriteSize.x) / 2.f;
				pos.y = sliderRenderSize.y / 2.f;
				margin.y = GetBackgroundMargin();
			}
			m_backEntity->GetComponent<NodeComponent>().SetPosition(pos + sliderPos);
			m_backSprite->SetSize(spriteSize);
			m_backSprite->SetSliceMargin(margin.y, margin.y, margin.x, margin.x);
		}
		else m_backEntity->Disable();

		m_textEntity->Enable(m_textEnabled && isVisible);
		if (m_textEnabled)
		{
			UpdateText();
			m_textEntity->GetComponent<NodeComponent>().SetPosition(GetTextPos());
		}
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

		if (m_textPosition == ButtonTextAlignment_TopLeft || m_textPosition == ButtonTextAlignment_TopRight || m_textPosition == ButtonTextAlignment_Top
			|| m_textPosition == ButtonTextAlignment_DownLeft || m_textPosition == ButtonTextAlignment_DownRight || m_textPosition == ButtonTextAlignment_Down)
			size.y += m_textMaxSize.y;
		if (m_textPosition == ButtonTextAlignment_TopLeft || m_textPosition == ButtonTextAlignment_DownLeft || m_textPosition == ButtonTextAlignment_Left
			|| m_textPosition == ButtonTextAlignment_TopRight || m_textPosition == ButtonTextAlignment_DownRight || m_textPosition == ButtonTextAlignment_Right)
			size.x += m_textMaxSize.x;

		size.x = std::max(size.x, m_textMaxSize.x);
		size.y = std::max(size.y, m_textMaxSize.y);

		SetPreferredSize(size);
	}

	ButtonState SimpleSliderWidget::GetCurrentState() const
	{
		if (!IsEnabled())
			return ButtonState_Disabled;
		if (m_pressed)
			return ButtonState_Pressed;
		if (m_hovered)
			return ButtonState_Hovered;
		return ButtonState_Idle;
	}

	void SimpleSliderWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{
		Nz::Vector2f size = GetSliderSize();
		Nz::Vector2f pos = GetSliderPos();
		SliderOrientation orientation = GetOrientation();

		Nz::Rectf buttonRect = GetButtonRect();

		bool hoveredOld = m_hovered;
		SetHovered(buttonRect.Contains(static_cast<float>(x), static_cast<float>(y)));
		if (!m_pressed && m_hovered != hoveredOld)
			Layout();

		if (m_pressed)
		{
			float normalizedValue = 0;
			if (orientation == SliderOrientation_Horizontal)
				normalizedValue = (x - m_pressOffset - pos.x) / (size.x - buttonRect.width);
			else normalizedValue = (y - m_pressOffset - pos.y) / (size.y - buttonRect.height);

			SetNormalizedValue(normalizedValue);
		}

		if (m_backgroundPressed)
		{
			if (orientation == SliderOrientation_Horizontal)
				m_pressOffset = x - buttonRect.x - pos.x - buttonRect.width / 2;
			else m_pressOffset = y - buttonRect.y - pos.y - buttonRect.height / 2;
		}
	}

	void SimpleSliderWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{
		Nz::Rectf buttonRect = GetButtonRect();

		if (buttonRect.Contains(static_cast<float>(x), static_cast<float>(y)))
		{
			SetPressed(true);
			if (GetOrientation() == SliderOrientation_Horizontal)
				m_pressOffset = x - buttonRect.x;
			else m_pressOffset = y - buttonRect.y;
		}
		else
		{
			SetBackgroundPressed(true);

			if (GetOrientation() == SliderOrientation_Horizontal)
				m_pressOffset = x - buttonRect.x - buttonRect.width / 2;
			else m_pressOffset = y - buttonRect.y - buttonRect.height / 2;
		}

		Layout();
	}

	void SimpleSliderWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{
		m_pressOffset = 0;

		SetBackgroundPressed(false);
		SetPressed(false);

		Layout();
	}

	void SimpleSliderWidget::OnMouseExit()
	{
		m_pressOffset = 0;

		SetBackgroundPressed(false);
		SetPressed(false);
		SetHovered(false);

		Layout();
	}

	void SimpleSliderWidget::Update(float elapsedTime)
	{
		if (!m_backgroundPressed)
			return;

		float distance = elapsedTime * m_moveSpeed;
		if (distance > std::abs(m_pressOffset))
			distance = m_pressOffset;
		else if (m_pressOffset < 0)
			distance *= -1;

		Nz::Vector2f size = GetSliderSize();
		Nz::Vector2f pos = GetSliderPos();
		SliderOrientation orientation = GetOrientation();

		Nz::Rectf buttonRect = GetButtonRect();
		buttonRect.x -= pos.x;
		buttonRect.y -= pos.y;

		float value = 0;
		if (orientation == SliderOrientation_Horizontal)
			value = (buttonRect.x + distance) / (size.x - buttonRect.width);
		else value = (buttonRect.y + distance) / (size.y - buttonRect.height);

		m_pressOffset -= distance;

		if (orientation == SliderOrientation_Horizontal && std::abs(m_pressOffset) < buttonRect.width / 2.f)
			SetHovered(true);
		if (orientation == SliderOrientation_Vertical && std::abs(m_pressOffset) < buttonRect.height / 2.f)
			SetHovered(true);

		SetNormalizedValue(value);
	}

	Nz::Rectf SimpleSliderWidget::GetButtonRect() const
	{
		Nz::Vector2f size = GetSliderSize();
		Nz::Vector2f basePos = GetSliderPos();
		ButtonState state = GetCurrentState();
		SliderOrientation orientation = GetOrientation();
		const TextureInfo &infos = m_sliderDatas[orientation][state];

		Nz::Vector2f sliderSize(32, 32);
		Nz::Vector2f sliderRenderSize(size);

		if (!infos.texture.IsValid())
			return sliderRenderSize;

		sliderSize.x = infos.texture->GetWidth() * infos.textureCoords.width;
		sliderSize.y = infos.texture->GetHeight() * infos.textureCoords.height;

		Nz::Vector2f pos(0, 0);

		if (orientation == SliderOrientation_Horizontal)
		{
			sliderRenderSize.y = size.y;
			sliderRenderSize.x = sliderRenderSize.y / sliderSize.y * sliderSize.x;
			pos.x = GetNormalizedValue() * (size.x - sliderRenderSize.x);
		}
		else
		{
			sliderRenderSize.x = size.x;
			sliderRenderSize.y = sliderRenderSize.x / sliderSize.x * sliderSize.y;
			pos.y = GetNormalizedValue() * (size.y - sliderRenderSize.y);
		}

		return Nz::Rectf(basePos.x + pos.x, basePos.y + pos.y, sliderRenderSize.x, sliderRenderSize.y);
	}


	void SimpleSliderWidget::UpdateTextSize()
	{
		//assuming that the 0 character is the bigger of this font

		float min = std::abs(GetMin());
		float max = std::abs(GetMax());

		unsigned int nbChar = 1;
		if (min > max && min > 1)
			nbChar = static_cast<unsigned int>(std::log10(min));
		if(max > min && max > 1)
			nbChar = static_cast<unsigned int>(std::log10(max));

		if (m_textPrecision > 0)
			nbChar += m_textPrecision + 1;
		if (GetMin() < 0 || GetMax() < 0)
			nbChar++;

		std::string str(nbChar, '0');

		Nz::SimpleTextDrawer drawer = m_textFont.IsValid() ?
			Nz::SimpleTextDrawer::Draw(m_textFont, str, m_textCharacterSize, m_textStyle, m_textColor) :
			Nz::SimpleTextDrawer::Draw(str, m_textCharacterSize, m_textStyle, m_textColor);

		Nz::Recti size = drawer.GetBounds();

		m_textMaxSize.x = static_cast<float>(size.width);
		m_textMaxSize.y = static_cast<float>(size.height);

		UpdatePreferedSize();

		Layout();
	}

	void SimpleSliderWidget::UpdateText()
	{
		if (!m_textEnabled)
			return;

		std::ostringstream streamValue;
		streamValue.precision(m_textPrecision);
		streamValue << std::fixed << GetValue();

		Nz::SimpleTextDrawer drawer = m_textFont.IsValid() ?
			Nz::SimpleTextDrawer::Draw(m_textFont, streamValue.str(), m_textCharacterSize, m_textStyle, m_textColor) :
			Nz::SimpleTextDrawer::Draw(streamValue.str(), m_textCharacterSize, m_textStyle, m_textColor);

		Nz::Recti size = drawer.GetBounds();

		m_textSize.x = static_cast<float>(size.width);
		m_textSize.y = static_cast<float>(size.height);

		m_textSprite->Update(drawer);
	}
}
