#pragma once
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "byteCat/ecs/Entity.h"

namespace BC
{
	namespace Ecs
	{
		struct Light : Component
		{
			glm::vec3 color;

			Light(glm::vec3 color): color(color) {}
			virtual ~Light() = default;

			TYPE_NAME("Light")
		};

		struct DirectionalLight : Light
		{
			glm::vec3 direction;

			DirectionalLight(glm::vec3 direction, glm::vec3 color): Light(color), direction(direction) {}
		};
	}
}
