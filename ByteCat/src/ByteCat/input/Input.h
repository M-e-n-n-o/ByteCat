#pragma once

#include <glm/glm.hpp>
#include "byteCat/input/KeyCodes.h"
#include "byteCat/input/MouseCodes.h"

namespace BC
{
	namespace Input
	{
		bool IsKeyPressed(KeyCode key);
		
		bool IsMouseButtonPressed(MouseCode button);
		glm::vec2 GetMousePos();
	};
}
