
#include <NDK/Widgets/Simple/SimpleRadioButtonWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>

namespace Ndk
{
	const std::string SimpleRadioButtonWidget::s_buttonIdleName("Ndk::RadioButton::idle");
	const std::string SimpleRadioButtonWidget::s_buttonHoveredName("Ndk::RadioButton::hovered");
	const std::string SimpleRadioButtonWidget::s_buttonDisabledName("Ndk::RadioButton::disabled");
	const std::string SimpleRadioButtonWidget::s_checkmarkName("Ndk::RadioButton::check");

	SimpleRadioButtonWidget::SimpleRadioButtonWidget(BaseWidget* parent)
		: TexturedButtonWidget(parent)
	{
		m_checkSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));

		m_checkEntity = CreateEntity();
		m_checkEntity->AddComponent<NodeComponent>().SetParent(this);
		m_checkEntity->AddComponent<GraphicsComponent>().Attach(m_checkSprite, TexturedButtonWidget::GetRenderOrderIndex() + 1);

		SetTexture(Nz::TextureLibrary::Get(s_buttonIdleName)); //idle texture on all state
		SetTexture(Nz::TextureLibrary::Get(s_buttonHoveredName), Ndk::ButtonState_Hovered);
		SetTexture(Nz::TextureLibrary::Get(s_buttonHoveredName), Ndk::ButtonState_PressedHovered);
		SetTexture(Nz::TextureLibrary::Get(s_buttonDisabledName), Ndk::ButtonState_Disabled);

		SetCheckTexture(Nz::TextureLibrary::Get(s_checkmarkName), true);

		EnableRadioButton(true);
		SetTextPosition(Ndk::ButtonTextAlignment_Right);
		SetKeepTextureRatio(true);

		Layout();
	}

	bool SimpleRadioButtonWidget::Initialize()
	{
		const Nz::UInt8 r_idle[] =
		{
			#include <NDK/Resources/Widgets/RadioBack.png.h>
		};

		const Nz::UInt8 r_hovered[] =
		{
			#include <NDK/Resources/Widgets/RadioBackHovered.png.h>
		};

		const Nz::UInt8 r_disabled[] =
		{
			#include <NDK/Resources/Widgets/RadioBackDisabled.png.h>
		};

		const Nz::UInt8 r_check[] =
		{
			#include <NDK/Resources/Widgets/RadioDot.png.h>
		};

		Nz::TextureRef idleTexture = Nz::Texture::LoadFromMemory(r_idle, sizeof(r_idle) / sizeof(r_idle[0]));
		if (!idleTexture)
		{
			NazaraError("Failed to load embedded Widgets/RadioBack.png");
			return false;
		}

		Nz::TextureRef hoveredTexture = Nz::Texture::LoadFromMemory(r_hovered, sizeof(r_hovered) / sizeof(r_hovered[0]));
		if (!hoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/RadioBackHovered.png");
			return false;
		}

		Nz::TextureRef disabledTexture = Nz::Texture::LoadFromMemory(r_disabled, sizeof(r_disabled) / sizeof(r_disabled[0]));
		if (!disabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/RadioBackDisabled.png");
			return false;
		}

		Nz::TextureRef checkTexture = Nz::Texture::LoadFromMemory(r_check, sizeof(r_check) / sizeof(r_check[0]));
		if (!checkTexture)
		{
			NazaraError("Failed to load embedded Widgets/RadioDot.png");
			return false;
		}

		Nz::TextureLibrary::Register(s_buttonIdleName, std::move(idleTexture));
		Nz::TextureLibrary::Register(s_buttonHoveredName, std::move(hoveredTexture));
		Nz::TextureLibrary::Register(s_buttonDisabledName, std::move(disabledTexture));
		Nz::TextureLibrary::Register(s_checkmarkName, std::move(checkTexture));

		return true;
	}

	void SimpleRadioButtonWidget::Uninitialize()
	{
		Nz::TextureLibrary::Unregister(s_buttonIdleName);
		Nz::TextureLibrary::Unregister(s_buttonHoveredName);
		Nz::TextureLibrary::Unregister(s_buttonDisabledName);
		Nz::TextureLibrary::Unregister(s_checkmarkName);
	}

	int SimpleRadioButtonWidget::GetRenderOrderIndex() const
	{
		return TexturedButtonWidget::GetRenderOrderIndex() + 1;
	}

	void SimpleRadioButtonWidget::Layout()
	{
		TexturedButtonWidget::Layout();

		if (m_checkSprite == nullptr)
			return;

		Nz::Rectf buttonRect = GetButtonRect();
		Nz::Vector2f buttonCenter(buttonRect.x + buttonRect.width / 2, buttonRect.y + buttonRect.height / 2);

		bool checked = IsChecked();
		ButtonInfo & infos = checked ? m_checkedData : m_uncheckedData;

		bool isVisible = IsVisible();

		if (infos.texture.IsValid())
		{
			m_checkEntity->Enable(isVisible);

			auto checkSize = infos.texture->GetSize();

			Nz::Vector2f size(buttonRect.height * checkSize.x / checkSize.y, buttonRect.height);

			m_checkSprite->SetTexture(infos.texture, false);
			m_checkSprite->SetTextureCoords(infos.textureCoords);
			m_checkSprite->SetColor(infos.color);
			m_checkSprite->SetSize(size);

			m_checkEntity->GetComponent<NodeComponent>().SetPosition(buttonCenter - size / 2.f);
		}
		else
		{
			m_checkEntity->Disable();
		}
	}
}
