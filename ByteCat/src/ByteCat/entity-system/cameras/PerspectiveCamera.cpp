#include "bcpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "byteCat/app/Application.h"
#include "byteCat/entity-system/cameras/PerspectiveCamera.h"

namespace BC
{
	PerspectiveCamera::PerspectiveCamera(float fov, float nearPlane, float farPlane)
	{
		int width = Application::GetInstance().getWindow().getWidth();
		int height = Application::GetInstance().getWindow().getHeight();

		projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(width / height), nearPlane, farPlane);
	}

	void PerspectiveCamera::setPerspective(float fov, float nearPlane, float farPlane)
	{
		int width = Application::GetInstance().getWindow().getWidth();
		int height = Application::GetInstance().getWindow().getHeight();

		projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(width / height), nearPlane, farPlane);
	}
}
