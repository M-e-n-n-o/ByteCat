#pragma once
#include <glm/vec3.hpp>
#include "byteCat/ecs/Entity.h"

namespace BC
{
	struct Transform : Component
	{		
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform() = default;
		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
			: position(position),
			  rotation(rotation),
			  scale(scale)
		{
		}

		TYPE_NAME("Transform")
	};
}
