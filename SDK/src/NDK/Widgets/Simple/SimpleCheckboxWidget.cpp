
#include <NDK/Widgets/Simple/SimpleCheckboxWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>

namespace Ndk
{
	const std::string SimpleCheckboxWidget::s_buttonIdleName("Ndk::Checkbox::idle");
	const std::string SimpleCheckboxWidget::s_buttonHoveredName("Ndk::Checkbox::hovered");
	const std::string SimpleCheckboxWidget::s_buttonDisabledName("Ndk::Checkbox::disabled");
	const std::string SimpleCheckboxWidget::s_checkmarkName("Ndk::Checkbox::check");
	const std::string SimpleCheckboxWidget::s_ckeckTristateName("Ndk::Checkbox::tristate");

	SimpleCheckboxWidget::SimpleCheckboxWidget(BaseWidget* parent)
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

		SetCheckTexture(Nz::TextureLibrary::Get(s_checkmarkName), Ndk::CheckboxState_Checked);
		SetCheckTexture(Nz::TextureLibrary::Get(s_ckeckTristateName), Ndk::CheckboxState_Tristate);

		SetCheckable(true);
		SetTextPosition(Ndk::ButtonTextAlignment_Right);
		SetKeepTextureRatio(true);

		Layout();
	}

	bool SimpleCheckboxWidget::Initialize()
	{
		const Nz::UInt8 r_idle[] =
		{
			#include <NDK/Resources/Widgets/CheckboxBack.png.h>
		};

		const Nz::UInt8 r_hovered[] =
		{
			#include <NDK/Resources/Widgets/CheckboxBackHovered.png.h>
		};

		const Nz::UInt8 r_disabled[] =
		{
			#include <NDK/Resources/Widgets/CheckboxBackDisabled.png.h>
		};

		const Nz::UInt8 r_check[] =
		{
			#include <NDK/Resources/Widgets/CheckboxCheck.png.h>
		};

		const Nz::UInt8 r_tristate[] =
		{
			#include <NDK/Resources/Widgets/CheckboxTristate.png.h>
		};

		Nz::TextureRef idleTexture = Nz::Texture::LoadFromMemory(r_idle, sizeof(r_idle) / sizeof(r_idle[0]));
		if (!idleTexture)
		{
			NazaraError("Failed to load embedded Widgets/CheckboxBack.png");
			return false;
		}

		Nz::TextureRef hoveredTexture = Nz::Texture::LoadFromMemory(r_hovered, sizeof(r_hovered) / sizeof(r_hovered[0]));
		if (!hoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/CheckboxBackHovered.png");
			return false;
		}

		Nz::TextureRef disabledTexture = Nz::Texture::LoadFromMemory(r_disabled, sizeof(r_disabled) / sizeof(r_disabled[0]));
		if (!disabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/CheckboxBackDisabled.png");
			return false;
		}

		Nz::TextureRef checkTexture = Nz::Texture::LoadFromMemory(r_check, sizeof(r_check) / sizeof(r_check[0]));
		if (!checkTexture)
		{
			NazaraError("Failed to load embedded Widgets/CheckboxCheck.png");
			return false;
		}

		Nz::TextureRef tristateTexture = Nz::Texture::LoadFromMemory(r_tristate, sizeof(r_tristate) / sizeof(r_tristate[0]));
		if (!tristateTexture)
		{
			NazaraError("Failed to load embedded Widgets/CheckboxTristate.png");
			return false;
		}

		Nz::TextureLibrary::Register(s_buttonIdleName, std::move(idleTexture));
		Nz::TextureLibrary::Register(s_buttonHoveredName, std::move(hoveredTexture));
		Nz::TextureLibrary::Register(s_buttonDisabledName, std::move(disabledTexture));
		Nz::TextureLibrary::Register(s_checkmarkName, std::move(checkTexture));
		Nz::TextureLibrary::Register(s_ckeckTristateName, std::move(tristateTexture));

		return true;
	}

	void SimpleCheckboxWidget::Uninitialize()
	{
		Nz::TextureLibrary::Unregister(s_buttonIdleName);
		Nz::TextureLibrary::Unregister(s_buttonHoveredName);
		Nz::TextureLibrary::Unregister(s_buttonDisabledName);
		Nz::TextureLibrary::Unregister(s_checkmarkName);
		Nz::TextureLibrary::Unregister(s_ckeckTristateName);
	}

	int SimpleCheckboxWidget::GetRenderOrderIndex() const
	{
		return TexturedButtonWidget::GetRenderOrderIndex() + 1;
	}

	void SimpleCheckboxWidget::Layout()
	{
		TexturedButtonWidget::Layout();

		if (m_checkSprite == nullptr)
			return;

		bool isVisible = IsVisible();

		Nz::Rectf buttonRect = GetButtonRect();
		Nz::Vector2f buttonCenter(buttonRect.x + buttonRect.width / 2, buttonRect.y + buttonRect.height / 2);

		auto state = GetCheckState();
		if (m_checkDatas[state].texture.IsValid())
		{
			m_checkEntity->Enable(isVisible);

			auto checkSize = m_checkDatas[state].texture->GetSize();

			Nz::Vector2f size(buttonRect.height * checkSize.x / checkSize.y, buttonRect.height);

			m_checkSprite->SetTexture(m_checkDatas[state].texture, false);
			m_checkSprite->SetTextureCoords(m_checkDatas[state].textureCoords);
			m_checkSprite->SetColor(m_checkDatas[state].color);
			m_checkSprite->SetSize(size);

			m_checkEntity->GetComponent<NodeComponent>().SetPosition(buttonCenter - size / 2.f);
		}
		else
		{
			m_checkEntity->Disable();
		}
	}
}
