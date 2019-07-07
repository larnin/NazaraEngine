
#include <NDK/Widgets/Simple/SimpleButtonWidget.hpp>

namespace Ndk
{
	const std::string SimpleButtonWidget::s_buttonIdleName("Ndk::Button::idle");
	const std::string SimpleButtonWidget::s_buttonHoveredName("Ndk::Button::hovered");
	const std::string SimpleButtonWidget::s_buttonPressedName("Ndk::Button::pressed");
	const std::string SimpleButtonWidget::s_buttonPressedHoveredName("Ndk::Button::pressedHovered");
	const std::string SimpleButtonWidget::s_buttonDisabledName("Ndk::Button::disabled");
	const unsigned int SimpleButtonWidget::s_sliceSize(25u);

	SimpleButtonWidget::SimpleButtonWidget(BaseWidget* parent)
		: TexturedButtonWidget(parent)
	{
		SetTexture(Nz::TextureLibrary::Get(s_buttonIdleName), Ndk::ButtonState_Idle);
		SetTexture(Nz::TextureLibrary::Get(s_buttonHoveredName), Ndk::ButtonState_Hovered);
		SetTexture(Nz::TextureLibrary::Get(s_buttonPressedName), Ndk::ButtonState_Pressed);
		SetTexture(Nz::TextureLibrary::Get(s_buttonPressedHoveredName), Ndk::ButtonState_PressedHovered);
		SetTexture(Nz::TextureLibrary::Get(s_buttonDisabledName), Ndk::ButtonState_Disabled);

		SetSliceMargin(s_sliceSize);
	}

	bool SimpleButtonWidget::Initialize()
	{
		const Nz::UInt8 r_idle[] =
		{
			#include <NDK/Resources/Widgets/Button.png.h>
		};

		const Nz::UInt8 r_hovered[] =
		{
			#include <NDK/Resources/Widgets/ButtonHovered.png.h>
		};

		const Nz::UInt8 r_pressed[] =
		{
			#include <NDK/Resources/Widgets/ButtonPressed.png.h>
		};

		const Nz::UInt8 r_pressedHovered[] =
		{
			#include <NDK/Resources/Widgets/ButtonPressedHovered.png.h>
		};

		const Nz::UInt8 r_disabled[] =
		{
			#include <NDK/Resources/Widgets/ButtonDisabled.png.h>
		};


		Nz::TextureRef idleTexture = Nz::Texture::LoadFromMemory(r_idle, sizeof(r_idle) / sizeof(r_idle[0]));
		if (!idleTexture)
		{
			NazaraError("Failed to load embedded Widgets/Button.png");
			return false;
		}

		Nz::TextureRef hoveredTexture = Nz::Texture::LoadFromMemory(r_hovered, sizeof(r_hovered) / sizeof(r_hovered[0]));
		if (!hoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/ButtonHovered.png");
			return false;
		}

		Nz::TextureRef pressedTexture = Nz::Texture::LoadFromMemory(r_pressed, sizeof(r_pressed) / sizeof(r_pressed[0]));
		if (!pressedTexture)
		{
			NazaraError("Failed to load embedded Widgets/ButtonPressed.png");
			return false;
		}

		Nz::TextureRef pressedHoveredTexture = Nz::Texture::LoadFromMemory(r_pressedHovered, sizeof(r_pressedHovered) / sizeof(r_pressedHovered[0]));
		if (!pressedHoveredTexture)
		{
			NazaraError("Failed to load embedded Widgets/ButtonPressedHovered.png");
			return false;
		}

		Nz::TextureRef disabledTexture = Nz::Texture::LoadFromMemory(r_disabled, sizeof(r_disabled) / sizeof(r_disabled[0]));
		if (!disabledTexture)
		{
			NazaraError("Failed to load embedded Widgets/ButtonDisabled.png");
			return false;
		}

		Nz::TextureLibrary::Register(s_buttonIdleName, std::move(idleTexture));
		Nz::TextureLibrary::Register(s_buttonHoveredName, std::move(hoveredTexture));
		Nz::TextureLibrary::Register(s_buttonPressedName, std::move(pressedTexture));
		Nz::TextureLibrary::Register(s_buttonPressedHoveredName, std::move(pressedHoveredTexture));
		Nz::TextureLibrary::Register(s_buttonDisabledName, std::move(disabledTexture));

		return true;
	}

	void SimpleButtonWidget::Uninitialize()
	{
		Nz::TextureLibrary::Unregister(s_buttonIdleName);
		Nz::TextureLibrary::Unregister(s_buttonHoveredName);
		Nz::TextureLibrary::Unregister(s_buttonPressedName);
		Nz::TextureLibrary::Unregister(s_buttonPressedHoveredName);
		Nz::TextureLibrary::Unregister(s_buttonDisabledName);
	}
}
