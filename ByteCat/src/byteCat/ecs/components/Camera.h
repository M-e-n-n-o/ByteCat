#pragma once
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "byteCat/ecs/Entity.h"

namespace BC
{
	struct Camera : Component
	{
		Camera() = default;
		virtual ~Camera() = default;
	
		virtual glm::mat4 getProjectionMatrix(float aspectRatio) = 0;
	
		TYPE_NAME("Camera")
	};
	
	struct PerspectiveCamera : Camera
	{
		float fov;
		float nearPlane;
		float farPlane;
	
		PerspectiveCamera() = default;
		PerspectiveCamera(float fov, float nearPlane, float farPlane) : fov(fov), nearPlane(nearPlane), farPlane(farPlane) {}
	
		glm::mat4 getProjectionMatrix(float aspectRatio) override
		{
			return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
		}
	};

	struct OrtographicCamera : Camera
	{
		OrtographicCamera() = default;
		
		glm::mat4 getProjectionMatrix(float aspectRatio) override { return glm::mat4(1); }
	};
}
