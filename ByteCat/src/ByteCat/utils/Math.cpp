#include "bcpch.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	namespace Utils
	{
		glm::mat4& CreateModelMatrix(glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
		{
			glm::mat4 matrix(1.0f);
			matrix = glm::translate(matrix, translation);
			matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
			matrix = glm::scale(matrix, scale);
			return matrix;
		}
	}
}
