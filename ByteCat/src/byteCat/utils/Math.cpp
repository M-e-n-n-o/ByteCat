#include "bcpch.h"
#include "byteCat/utils/Math.h"
#include "glm/ext/matrix_transform.hpp"

namespace BC
{
	glm::mat4 Math::CreateModelMatrix(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, glm::vec3(pos.x, pos.y, pos.z));
		matrix = glm::rotate(matrix, glm::radians(rot.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(rot.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(rot.z), glm::vec3(0, 0, 1));
		matrix = glm::scale(matrix, scale);
		return matrix;
	}

	glm::mat4 Math::CreateViewMatrix(const glm::vec3& pos, const glm::vec3& rot)
	{
		glm::mat4 viewMatrix(1.0f);
		viewMatrix = glm::rotate(viewMatrix, glm::radians(rot.x), glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(rot.y), glm::vec3(0, 1, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(rot.z), glm::vec3(0, 0, 1));
		const glm::vec3 negativePos = glm::vec3(-pos.x, -pos.y, -pos.z);
		viewMatrix = glm::translate(viewMatrix, negativePos);
		return viewMatrix;
	}
}
