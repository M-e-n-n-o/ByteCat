#include "bcpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "byteCat/entity-system/cameras/OrthographicCamera.h"

namespace BC
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearP, float farP): Camera()
	{
		projectionMatrix = glm::ortho(left, right, bottom, top, nearP, farP);
	}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top, float nearP, float farP)
	{
		projectionMatrix = glm::ortho(left, right, bottom, top, nearP, farP);
	}
}
