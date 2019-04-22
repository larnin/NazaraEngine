#include <NDK/Widgets/SpinBoxWidget.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <NDK/Components/GraphicsComponent.hpp>

namespace Ndk
{
	Nz::Color SpinBoxWidget::s_buttonBaseColor{ 200, 200, 200 };
	Nz::Color SpinBoxWidget::s_buttonHoveredColor{ 220, 220, 220 };
	Nz::Color SpinBoxWidget::s_buttonPressedColor{ 255, 255, 255 };
	float SpinBoxWidget::s_buttonsSpacing{ 5 };

	SpinBoxWidget::SpinBoxWidget(BaseWidget* parent) :
	BaseWidget(parent),
	m_textArea(nullptr),
	m_value(0.f),
	m_minValue(0.f),
	m_maxValue(100.f),
	m_step(1.f),
	m_precision(3),
	m_pressedButton(HoveredButton::noButton),
	m_blockTextChangeSignal(false)
	{
		m_topButtonSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_topButtonSprite->SetColor(s_buttonBaseColor);
		m_topButtonSprite->SetTexture(Nz::TextureLibrary::Get("Ndk::ScrollBarWidget::scrollbarbutton"), false);

		m_bottomButtonSprite = Nz::Sprite::New(Nz::Material::New("Translucent2D"));
		m_bottomButtonSprite->SetColor(s_buttonBaseColor);
		m_bottomButtonSprite->SetTexture(Nz::TextureLibrary::Get("Ndk::ScrollBarWidget::scrollbarbutton"), false);

		m_topButtonEntity = CreateEntity();
		m_topButtonEntity->AddComponent<Ndk::NodeComponent>().SetParent(this);
		Nz::Matrix4f topMat = Nz::Matrix4f::Rotate(Nz::Quaternionf(Nz::EulerAnglesf(0, 0, 180)));
		m_topButtonEntity->AddComponent<Ndk::GraphicsComponent>().Attach(m_topButtonSprite, topMat);

		m_bottomButtonEntity = CreateEntity();
		m_bottomButtonEntity->AddComponent<Ndk::NodeComponent>().SetParent(this);
		m_bottomButtonEntity->AddComponent<Ndk::GraphicsComponent>().Attach(m_bottomButtonSprite);

		m_textArea = Add<TextAreaWidget>();
		m_textArea->SetCharacterFilter([](const auto & c) {return c == '-' || c == '.' || (c >= '0' && c <= '9'); }); //only numbers
		m_textArea->OnEditingFinished.Connect([this](const Ndk::TextAreaWidget*, const Nz::String & text) {OnTextChanged(text.ToStdString()); });
		SetValue(m_value);
	}

	void SpinBoxWidget::OnLayout()
	{
		Nz::Vector2f size = GetSize();

		Nz::Vector3ui buttonSpriteSize = m_topButtonSprite->GetMaterial()->GetDiffuseMap()->GetSize();
		Nz::Vector2f buttonSize{ 0, (size.y - s_buttonsSpacing) / 2.f };
		buttonSize.x = buttonSize.y * buttonSpriteSize.x / buttonSpriteSize.y;

		m_topButtonSprite->SetSize(buttonSize);
		m_bottomButtonSprite->SetSize(buttonSize);

		if(m_textArea != nullptr)
			m_textArea->Resize(Nz::Vector2f(size.x - buttonSize.x - s_buttonsSpacing, size.y));

		m_topButtonEntity->GetComponent<Ndk::NodeComponent>().SetPosition(size.x, buttonSize.y);
		m_bottomButtonEntity->GetComponent<Ndk::NodeComponent>().SetPosition(size.x - buttonSize.x, buttonSize.y + s_buttonsSpacing);

		if (m_textArea != nullptr)
		{
			Nz::Vector2f preferedSize = m_textArea->GetPreferredSize();
			preferedSize.x += (preferedSize.y - s_buttonsSpacing) / 2.f * buttonSpriteSize.x / buttonSpriteSize.y;
			SetPreferredSize(preferedSize);
			SetMinimumSize(m_textArea->GetMinimumSize());
		}
			
	}

	void SpinBoxWidget::OnTextChanged(const std::string & text)
	{
		if (m_blockTextChangeSignal)
			return;

		try
		{
			float value = std::stof(text);
			SetValue(value);
		}
		catch (const std::exception &)
		{
			SetValue(m_value);
		}

	}

	void SpinBoxWidget::SetValue(float value)
	{
		m_value = value;

		CheckValueBounds();

		unsigned int nbChar = static_cast<unsigned int>(std::log10(std::abs(m_value))) + 1;
		std::string text = std::to_string(m_value);
		if (m_precision > 0)
			nbChar += m_precision + 1; //1.23
		if (m_value < 0)
			nbChar++; //-12.3
		text = text.substr(0, nbChar);
		m_blockTextChangeSignal = true;
		m_textArea->SetText(text);
		m_blockTextChangeSignal = false;
	}

	void SpinBoxWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{
		HoveredButton currentButton = GetButton(Nz::Vector2f(static_cast<float>(x), static_cast<float>(y)));

		m_topButtonSprite->SetColor(s_buttonBaseColor);
		m_bottomButtonSprite->SetColor(s_buttonBaseColor);

		if (currentButton == HoveredButton::topButton)
			m_topButtonSprite->SetColor(s_buttonHoveredColor);
		if (currentButton == HoveredButton::bottomButton)
			m_bottomButtonSprite->SetColor(s_buttonHoveredColor);

		if (m_pressedButton == HoveredButton::topButton)
			m_topButtonSprite->SetColor(s_buttonPressedColor);
		if (m_pressedButton == HoveredButton::bottomButton)
			m_bottomButtonSprite->SetColor(s_buttonPressedColor);
	}

	void SpinBoxWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left)
		{
			m_pressedButton = GetButton(Nz::Vector2f(static_cast<float>(x), static_cast<float>(y)));
			OnMouseMoved(x, y, 0, 0);

			if (m_pressedButton == HoveredButton::topButton)
				SetValue(m_value + m_step);
			if (m_pressedButton == HoveredButton::bottomButton)
				SetValue(m_value - m_step);
		}
	}

	void SpinBoxWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left)
		{
			if (m_pressedButton == HoveredButton::topButton)
				m_topButtonSprite->SetColor(s_buttonHoveredColor);
			if (m_pressedButton == HoveredButton::bottomButton)
				m_bottomButtonSprite->SetColor(s_buttonHoveredColor);

			m_pressedButton = HoveredButton::noButton;
		}
	}

	void SpinBoxWidget::OnMouseExit()
	{
		m_topButtonSprite->SetColor(s_buttonBaseColor);
		m_bottomButtonSprite->SetColor(s_buttonBaseColor);

		m_pressedButton = HoveredButton::noButton;
	}

	SpinBoxWidget::HoveredButton SpinBoxWidget::GetButton(const Nz::Vector2f & pos) const
	{
		Nz::Vector2f size = GetSize();

		Nz::Vector2f buttonSpriteSize = m_topButtonSprite->GetSize();
		Nz::Vector2f buttonSize{ 0, (size.y - s_buttonsSpacing) / 2.f };
		buttonSize.x = buttonSize.y * buttonSpriteSize.x / buttonSpriteSize.y;

		if (pos.x < size.x - buttonSize.x)
			return HoveredButton::noButton;

		if (pos.y < buttonSize.y)
			return HoveredButton::topButton;

		if (pos.y > buttonSize.y + s_buttonsSpacing)
			return HoveredButton::bottomButton;
		return HoveredButton::noButton;
	}

	void SpinBoxWidget::CheckValueBounds()
	{
		float min = std::min(m_minValue, m_maxValue);
		float max = std::max(m_minValue, m_maxValue);

		if (m_value < min)
			SetValue(min);
		else if (m_value > max)
			SetValue(max);
	}
}
