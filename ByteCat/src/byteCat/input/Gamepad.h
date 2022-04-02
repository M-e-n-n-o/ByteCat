#pragma once

namespace BC
{
	enum class GamepadID
	{
		ID_1  = 0,
		ID_2  = 1,
		ID_3  = 2,
		ID_4  = 3,
		ID_5  = 4,
		ID_6  = 5,
		ID_7  = 6,
		ID_8  = 7,
		ID_9  = 8,
		ID_10 = 9,
		ID_11 = 10,
		ID_12 = 11,
		ID_13 = 12,
		ID_14 = 13,
		ID_15 = 14,
		ID_16 = 15
	};
	
	struct Gamepad
	{
		GamepadID id;
		const char* name;
	};

	enum class GamepadButton
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LEFT_BUMPER = 4,
		RIGHT_BUMPER = 5,
		BACK = 6,
		START = 7,
		GUIDE = 8,
		LEFT_THUMB = 9,
		RIGHT_THUMB = 10,
		DPAD_UP = 11,
		DPAD_RIGHT = 12,
		DPAD_DOWN = 13,
		DPAD_LEFT = 14,

		CROSS = A,
		CIRCLE = B,
		SQUARE = X,
		TRIANGLE = Y
	};

	enum class GamepadAxis
	{
		LEFT_X = 0,
		LEFT_Y = 1,
		RIGHT_X = 2,
		RIGHT_Y = 3,
		LEFT_TRIGGER = 4,
		RIGHT_TRIGGER = 5
	};
}
