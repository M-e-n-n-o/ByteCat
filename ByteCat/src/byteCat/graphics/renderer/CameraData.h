#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace BC
{
	namespace Graphics
	{
		struct CameraData
		{
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;

			CameraData(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) : viewMatrix(viewMatrix), projectionMatrix(projectionMatrix) {}
		};
	}
}
