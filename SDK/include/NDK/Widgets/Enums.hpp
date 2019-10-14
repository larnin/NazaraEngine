// Copyright (C) 2017 Samy Bensaid
// This file is part of the "Nazara Development Kit"
// For conditions of distribution and use, see copyright notice in Prerequisites.hpp

#pragma once

#ifndef NAZARA_ENUMS_SDK_HPP
#define NAZARA_ENUMS_SDK_HPP

namespace Ndk
{
	enum BoxLayoutOrientation
	{
		BoxLayoutOrientation_Horizontal,
		BoxLayoutOrientation_Vertical
	};

	enum CheckboxState
	{
		CheckboxState_Checked,
		CheckboxState_Tristate,
		CheckboxState_Unchecked,

		CheckboxState_Max = CheckboxState_Unchecked,

		CheckboxState_All
	};

	enum ButtonState
	{
		ButtonState_Idle,
		ButtonState_Hovered,
		ButtonState_Pressed,
		ButtonState_PressedHovered,
		ButtonState_Disabled,

		ButtonState_Max = ButtonState_Disabled,

		ButtonState_All
	};

	enum ButtonTextAlignment
	{
		ButtonTextAlignment_TopLeft,
		ButtonTextAlignment_Left,
		ButtonTextAlignment_DownLeft,
		ButtonTextAlignment_Down,
		ButtonTextAlignment_DownRight,
		ButtonTextAlignment_Right,
		ButtonTextAlignment_TopRight,
		ButtonTextAlignment_Top,
		ButtonTextAlignment_Centred,

		ButtonTextAlignment_Max,
	};

	enum SliderOrientation
	{
		SliderOrientation_Horizontal,
		SliderOrientation_Vertical,

		SliderOrientation_Max = SliderOrientation_Vertical
	};

	enum ScrollBarButton
	{
		ScrollBarButton_Center,
		ScrollBarButton_Up,
		ScrollBarButton_Down,
		ScrollBarButton_Left,
		ScrollBarButton_Right,

		ScrollBarButton_Max = ScrollBarButton_Right
	};

	enum EchoMode
	{
		EchoMode_Normal,
		EchoMode_Password,
		EchoMode_PasswordExceptLast,

		EchoMode_Max = EchoMode_PasswordExceptLast
	};
}

#endif // NAZARA_ENUMS_SDK_HPP
