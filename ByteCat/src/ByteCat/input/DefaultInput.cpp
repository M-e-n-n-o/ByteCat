#include "bcpch.h"
#include "byteCat/input/Input.h"

#ifdef BC_PLATFORM_NONE

namespace BC
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		return false;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		return false;
	}

	glm::vec2 Input::getMousePos()
	{
		return { 0, 0 };
	}
}

#endif