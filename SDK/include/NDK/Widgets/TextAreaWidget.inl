// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Development Kit"
// For conditions of distribution and use, see copyright notice in Prerequesites.hpp

#include <NDK/Widgets/TextAreaWidget.hpp>

namespace Ndk
{
	inline void TextAreaWidget::Clear()
	{
		m_cursorPosition = 0;
		m_drawer.Clear();
		m_textSprite->Update(m_drawer);

		RefreshCursor();
	}

	inline std::size_t TextAreaWidget::GetLineCount() const
	{
		return m_drawer.GetLineCount();
	}

	inline const Nz::String& TextAreaWidget::GetText() const
	{
		return m_drawer.GetText();
	}
}