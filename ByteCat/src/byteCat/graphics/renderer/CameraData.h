#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace BC
{
	namespace Graphics
	{
		struct CameraData
		{
			glm::vec3 cameraPos;

			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;

			CameraData(glm::vec3 cameraPos, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) : cameraPos(cameraPos), viewMatrix(viewMatrix), projectionMatrix(projectionMatrix) {}
		};
	}
}
