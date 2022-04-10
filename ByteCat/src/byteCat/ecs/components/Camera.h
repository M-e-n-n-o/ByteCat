#pragma once
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "byteCat/ecs/Entity.h"

namespace BC
{
	namespace Ecs
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
			float left;
			float right;
			float top;
			float bottom;
			float nearPlane;
			float farPlane;

			OrtographicCamera() = default;
			OrtographicCamera(float left, float right, float top, float bottom, float nearPlane, float farPlane)
				: left(left), right(right), top(top), bottom(bottom), nearPlane(nearPlane), farPlane(farPlane) {}

			glm::mat4 getProjectionMatrix(float aspectRatio) override
			{
				return glm::ortho(left * aspectRatio, right * aspectRatio, bottom, top, nearPlane, farPlane);
			}
		};
	}
}
