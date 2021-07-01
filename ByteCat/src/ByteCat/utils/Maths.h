#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace BC
{
	namespace Utils
	{
		glm::mat4 CreateModelMatrix(glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
	}
}
