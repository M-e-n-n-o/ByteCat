#pragma once

#include <glm/glm.hpp>
#include "byteCat/input/KeyCodes.h"
#include "byteCat/input/MouseCodes.h"

namespace BC
{
	namespace Input
	{
		bool BYTECAT_API IsKeyPressed(KeyCode key);
		
		bool BYTECAT_API IsMouseButtonPressed(MouseCode button);
		glm::vec2 BYTECAT_API GetMousePos();
	};
}
