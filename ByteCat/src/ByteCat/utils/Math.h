#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace BC
{
	namespace Utils
	{
		// Use this function to create a transformation (model matrix) for an object in the application
		glm::mat4 CreateModelMatrix(glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
	}
}
