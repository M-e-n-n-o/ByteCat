#pragma once
#include <glm/vec3.hpp>
#include "byteCat/entity/Entity.h"

namespace BC
{
	struct Transform : Component
	{
		virtual ~Transform() = default;
		
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}
