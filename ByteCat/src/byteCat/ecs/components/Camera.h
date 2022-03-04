#pragma once
#include "byteCat/ecs/Entity.h"

#include "glm/mat4x4.hpp"

namespace BC
{
	struct Camera : Component
	{
		bool isPerspective;
		
		float fov;
		float nearPlane;
		float farPlane;
		
		Camera() = default;
		Camera(float fov, float nearPlane, float farPlane): isPerspective(true), fov(fov), nearPlane(nearPlane), farPlane(farPlane)
		{ }
	
		TYPE_NAME("Camera")
	};

	// struct Camera : Component
	// {
	//
	// 	Camera() = default;
	// 	virtual ~Camera() = default;
	//
	// 	virtual glm::mat4 getProjectionMatrix(float aspectRatio) = 0;
	//
	// 	TYPE_NAME("Camera")
	// };
	//
	// struct PerspectiveCamera : Camera
	// {
	// 	float fov;
	// 	float nearPlane;
	// 	float farPlane;
	//
	// 	PerspectiveCamera() = default;
	// 	PerspectiveCamera(float fov, float nearPlane, float farPlane) : fov(fov), nearPlane(nearPlane), farPlane(farPlane) {}
	//
	// 	glm::mat4 getProjectionMatrix(float aspectRatio) override
	// 	{
	// 		return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	// 	}
	// };
}
