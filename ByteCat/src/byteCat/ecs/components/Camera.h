#pragma once
#include "byteCat/ecs/Entity.h"

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
}
