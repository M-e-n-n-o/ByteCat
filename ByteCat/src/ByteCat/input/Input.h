#pragma once

#include <glm/glm.hpp>
#include "byteCat/Core.h"
#include "byteCat/input/KeyCodes.h"
#include "byteCat/input/MouseCodes.h"

namespace BC
{
	class BYTECAT_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 getMousePos();
	};
}
