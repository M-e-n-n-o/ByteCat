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

		projectionMatrix = glm::perspective(glm::radians(fov), ((width * 1.0f) / (height * 1.0f)), nearPlane, farPlane);

		this->fov = fov;
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;
	}

	void PerspectiveCamera::setPerspective(float fov, float nearPlane, float farPlane)
	{
		int width = Application::GetInstance().getWindow().getWidth();
		int height = Application::GetInstance().getWindow().getHeight();

		projectionMatrix = glm::perspective(glm::radians(fov), ((width * 1.0f) / (height * 1.0f)), nearPlane, farPlane);

		this->fov = fov;
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;
	}

	void PerspectiveCamera::onWindowResize(unsigned width, unsigned height)
	{
		projectionMatrix = glm::perspective(glm::radians(fov), ((width * 1.0f) / (height * 1.0f)), nearPlane, farPlane);
	}
}
