
#include <Nazara/Utility/SimpleTextDrawer.hpp>

#include <NDK/Widgets/SliderWidget.hpp>
#include <NDK/Components/GraphicsComponent.hpp>

#include <algorithm>

namespace Ndk
{
	Nz::Color SliderWidget::s_lineColor{ 200, 200, 200 };
	Nz::Color SliderWidget::s_cursorColor{ 128, 128, 128 };
	Nz::Color SliderWidget::s_cursorHoverColor{ 150, 150, 150 };
	Nz::Color SliderWidget::s_cursorPressColor{ 180, 180, 180 };
	float SliderWidget::s_cursorRatio{ 0.5f };
	float SliderWidget::s_lineRatio{ 0.1f };
	float SliderWidget::s_textHeight{ 2.f };
	float SliderWidget::s_charWidth{ 1.f };

	SliderWidget::SliderWidget(BaseWidget* parent) :
	BaseWidget(parent) ,
	m_minValue{ 0 },
	m_maxValue{ 100 },
	m_step{ 0 },
	m_value{ 0 },
	m_orientation{ SliderOrientation_Horizontal },
	m_textWidth{ 100.f },
	m_mousePressed{ false },
	m_showValue{ true },
	m_precision{ 3 },
	m_characterSize{ 25 }
	{
		m_lineSprite = Nz::Sprite::New(Nz::Material::New("Basic2D"));
		m_lineSprite->SetColor(s_lineColor);
		m_cursorSprite = Nz::Sprite::New(Nz::Material::New("Basic2D"));
		m_cursorSprite->SetColor(s_cursorColor);
		m_textSprite = Nz::TextSprite::New();

		m_lineEntity = CreateEntity();
		m_lineEntity->AddComponent<NodeComponent>().SetParent(this);
		m_lineEntity->AddComponent<GraphicsComponent>().Attach(m_lineSprite);

		m_cursorEntity = CreateEntity();
		m_cursorEntity->AddComponent<NodeComponent>().SetParent(this);
		m_cursorEntity->AddComponent<GraphicsComponent>().Attach(m_cursorSprite);

		m_textEntity = CreateEntity();
		m_textEntity->AddComponent<NodeComponent>().SetParent(this);
		m_textEntity->AddComponent<GraphicsComponent>().Attach(m_textSprite);

		UpdateText();
		UpdateSize();
		Layout();  
	}

	void SliderWidget::OnLayout()
	{
		BaseWidget::OnLayout();

		Nz::Vector2f cursorSize = GetCursorSize();
		Nz::Vector2f textSize = GetTextSize();
		Nz::Vector2f textSpriteSize = GetTextSpriteSize();
		Nz::Vector2f size = GetSize();
		Nz::Vector2f lineSize = GetLineSize();

		m_cursorSprite->SetSize(cursorSize);
		m_lineSprite->SetSize(lineSize);

		float normalizedValue = (m_value - m_minValue) / (m_maxValue - m_minValue);

		size_t principalAxis = m_orientation == SliderOrientation::SliderOrientation_Horizontal ? 0 : 1;
		size_t otherAxis = m_orientation == SliderOrientation::SliderOrientation_Horizontal ? 1 : 0;

		Nz::Vector2f cursorPosition{ 0, 0 };
		cursorPosition[principalAxis] = (size[principalAxis] - cursorSize[principalAxis] - textSize[principalAxis]) * normalizedValue;

		Nz::Vector2f linePosition = cursorSize / 2.0f;
		linePosition[otherAxis] -= lineSize[otherAxis] / 2.0f;

		m_cursorEntity->GetComponent<NodeComponent>().SetPosition(cursorPosition);
		m_lineEntity->GetComponent<NodeComponent>().SetPosition(linePosition);

		Nz::Vector2f textPosition{ cursorSize + lineSize - textSpriteSize};
		textPosition[principalAxis] += textSize[principalAxis];
		textPosition[otherAxis] /= 2.0f;

		m_textEntity->GetComponent<NodeComponent>().SetPosition(textPosition);
	}

	void SliderWidget::UpdateSize()
	{
		if (!m_showValue)
		{
			if (m_orientation == SliderOrientation::SliderOrientation_Horizontal)
				SetPreferredSize(Nz::Vector2f(s_charWidth * m_characterSize + 100.f, s_textHeight * m_characterSize));
			else SetPreferredSize( Nz::Vector2f(s_charWidth * m_characterSize, s_textHeight * m_characterSize + 100.f));
		}
		else
		{
			Nz::Vector2f size = GetTextSize();
			if (m_orientation == SliderOrientation::SliderOrientation_Horizontal)
				SetPreferredSize(Nz::Vector2f(size.x + 100.f, size.y));
			else SetPreferredSize(Nz::Vector2f(size.x, size.y + 100.f));
		}

		SetMinimumSize(GetPreferredSize());
	}

	void SliderWidget::UpdateText()
	{
		if (m_showValue)
		{
			unsigned int nbChar = static_cast<unsigned int>(std::log10(std::abs(m_value))) + 1;
			std::string text = std::to_string(m_value);
			if (m_precision > 0)
				nbChar += m_precision + 1; //1.23
			if (m_value < 0)
				nbChar++; //-12.3
			text = text.substr(0, nbChar);

			m_textEntity->Enable(true);
			m_textSprite->Update(Nz::SimpleTextDrawer::Draw(text, m_characterSize));
		}
		else m_textEntity->Enable(false);

		Layout();
	}

	void SliderWidget::OnMouseMoved(int x, int y, int deltaX, int deltaY)
	{
		if (!m_mousePressed)
			return;

		size_t axis = m_orientation == SliderOrientation::SliderOrientation_Horizontal ? 0 : 1;
		float pos = m_orientation == SliderOrientation::SliderOrientation_Horizontal ? static_cast<float>(x) : static_cast<float>(y);
		Nz::Vector2f cursorSize = GetCursorSize();
		Nz::Vector2f size = GetSize();
		Nz::Vector2f textSize = GetTextSize();

		float value = (pos - cursorSize[axis] / 2) / (size[axis] - textSize[axis] - cursorSize[axis]);
		value = std::max(value, 0.0f);
		value = std::min(value, 1.0f);

		if (m_step <= 0)
		{
			SetValue(value * (m_maxValue - m_minValue) + m_minValue);
			return;
		}

		float stepValue = m_step / (m_maxValue - m_minValue);
		int currentStep = static_cast<int>(std::round(value / stepValue));
		SetValue(stepValue * currentStep * (m_maxValue - m_minValue) + m_minValue);
	}

	void SliderWidget::OnMouseButtonPress(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left)
		{
			m_mousePressed = true;
			m_cursorSprite->SetColor(s_cursorPressColor);

			OnMouseMoved(x, y, 0, 0);
		}
	}

	void SliderWidget::OnMouseButtonRelease(int x, int y, Nz::Mouse::Button button)
	{
		if (button == Nz::Mouse::Left)
			OnMouseExit();
		m_cursorSprite->SetColor(s_cursorHoverColor);
	}

	void SliderWidget::OnMouseEnter()
	{
		m_cursorSprite->SetColor(s_cursorHoverColor);
	}

	void SliderWidget::OnMouseExit()
	{
		m_mousePressed = false;
		m_cursorSprite->SetColor(s_cursorColor);
	}
}
