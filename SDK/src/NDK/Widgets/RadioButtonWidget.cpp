
#include <NDK/Widgets/RadioButtonWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>

namespace Ndk
{
	Nz::Color RadioButtonWidget::s_backgroundColor{ Nz::Color::White };
	Nz::Color RadioButtonWidget::s_disabledBackgroundColor{ 201, 201, 201 };

	RadioButtonWidget::RadioButtonWidget(BaseWidget* parent):
	BaseWidget(parent),
	m_radioButtonEnabled { true },
	m_textMargin{ 16.f },
	m_state	{ false }
	{
		m_radioButtonBackgroundSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_radioButtonContentSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_textSprite = Nz::TextSprite::New();

		m_radioButtonBackgroundEntity = CreateEntity();
		m_radioButtonBackgroundEntity->AddComponent<NodeComponent>().SetParent(this);
		m_radioButtonBackgroundEntity->AddComponent<GraphicsComponent>().Attach(m_radioButtonBackgroundSprite);

		m_radioButtonContentEntity = CreateEntity();
		m_radioButtonContentEntity->AddComponent<NodeComponent>().SetParent(this);
		m_radioButtonContentEntity->AddComponent<GraphicsComponent>().Attach(m_radioButtonContentSprite, 2);

		m_textEntity = CreateEntity();
		m_textEntity->AddComponent<NodeComponent>().SetParent(this);
		m_textEntity->AddComponent<GraphicsComponent>().Attach(m_textSprite);

		m_background = Nz::TextureLibrary::Get("Ndk::RadioButtonWidget::radioBack");
		m_fill = Nz::TextureLibrary::Get("Ndk::RadioButtonWidget::radioFill");

		m_radioButtonBackgroundSprite->SetTexture(m_background, false);

		SetRadioButtonSize({ 32.f, 32.f });
		UpdateRadioButton();
	}

	void RadioButtonWidget::SetState(bool checked)
	{
		if (!m_radioButtonEnabled && checked)
			return;

		if (checked)
		{
			const Nz::Node* parent = GetParent();

			for (Node * child : parent->GetChilds())
			{
				RadioButtonWidget* radio = dynamic_cast<RadioButtonWidget*>(child);
				if (radio == nullptr)
					continue;
				radio->SetState(false);
			}
		}

		m_state = checked;
		UpdateRadioButton();
	}

	bool RadioButtonWidget::Initialize()
	{
		const Nz::UInt8 r_radioBack[] =
		{
			#include <NDK/Resources/radioBack.png.h>
		};

		Nz::TextureRef radioBackTexture = Nz::Texture::LoadFromMemory(r_radioBack, sizeof(r_radioBack) / sizeof(r_radioBack[0]));
		if (!radioBackTexture)
		{
			NazaraError("Failed to load embedded radioBack");
			return false;
		}

		Nz::TextureLibrary::Register("Ndk::RadioButtonWidget::radioBack", std::move(radioBackTexture));


		const Nz::UInt8 r_radioFill[] =
		{
			#include <NDK/Resources/radioFill.png.h>
		};

		Nz::TextureRef radioFillTexture = Nz::Texture::LoadFromMemory(r_radioFill, sizeof(r_radioFill) / sizeof(r_radioFill[0]));
		if (!radioFillTexture)
		{
			NazaraError("Failed to load embedded radioFill");
			return false;
		}

		Nz::TextureLibrary::Register("Ndk::RadioButtonWidget::radioFill", std::move(radioFillTexture));

		return true;
	}

	void RadioButtonWidget::Uninitialize()
	{
		Nz::TextureLibrary::Unregister("Ndk::RadioButtonWidget::radioBack");
		Nz::TextureLibrary::Unregister("Ndk::RadioButtonWidget::radioFill");
	}

	void RadioButtonWidget::Layout()
	{
		BaseWidget::Layout();

		Nz::Vector2f radioButtonSize = GetRadioButtonSize();

		Nz::Vector3f radioButtonBox = m_radioButtonContentSprite->GetBoundingVolume().obb.localBox.GetLengths();
		m_radioButtonContentEntity->GetComponent<NodeComponent>().SetPosition(radioButtonSize.x / 2.f - radioButtonBox.x / 2.f, radioButtonSize.y / 2.f - radioButtonBox.y / 2.f);

		Nz::Vector3f textBox = m_textSprite->GetBoundingVolume().obb.localBox.GetLengths();
		m_textEntity->GetComponent<NodeComponent>().SetPosition(radioButtonSize.x + m_textMargin, radioButtonSize.y / 2.f - textBox.y / 2.f);
	}

	void RadioButtonWidget::UpdateRadioButton()
	{
		if (m_radioButtonEnabled)
			m_radioButtonBackgroundSprite->SetColor(s_backgroundColor);
		else m_radioButtonBackgroundSprite->SetColor(s_disabledBackgroundColor);


		if (!m_state)
		{
			m_radioButtonContentEntity->Enable(false);
			return;
		}
		else
		{
			m_radioButtonContentEntity->Enable();
			m_radioButtonContentSprite->SetColor(Nz::Color::White);
			m_radioButtonContentSprite->SetTexture(m_fill, false);
		}
	}

	void RadioButtonWidget::UpdateSize()
	{
		Nz::Vector3f textSize = m_textSprite->GetBoundingVolume().obb.localBox.GetLengths();
		Nz::Vector2f checkboxSize = GetRadioButtonSize();

		Nz::Vector2f finalSize{ checkboxSize.x + m_textMargin + textSize.x, std::max(textSize.y, checkboxSize.y) };
		SetMinimumSize(finalSize);
		SetPreferredSize(finalSize);
	}

	void RadioButtonWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left && ContainsRadioButton(x, y) && IsRadioButtonEnabled())
		{
			SetState(!m_state);
			OnStateChanged(this);
		}
	}
}
