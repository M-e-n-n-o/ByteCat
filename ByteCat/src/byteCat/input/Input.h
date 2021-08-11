#pragma once

#include <glm/glm.hpp>
#include "byteCat/input/KeyCodes.h"
#include "byteCat/input/MouseCodes.h"

namespace BC
{
	namespace Input
	{
		// Call this function to check if a specific key is pressed
		bool IsKeyPressed(KeyCode key);

		// Call this function to see if a specific mouse button is pressed
		bool IsMouseButtonPressed(MouseCode button);
		// Call this function to get the current mouse position
		glm::vec2 GetMousePos();
	};
}
