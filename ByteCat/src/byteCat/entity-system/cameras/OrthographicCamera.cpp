#include "bcpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "byteCat/entity-system/cameras/OrthographicCamera.h"
#include "byteCat/app/Application.h"

namespace BC
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearP, float farP): Camera()
	{
		setProjection(left, right, bottom, top, nearP, farP);
	}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top, float nearP, float farP)
	{
		int width = Application::GetInstance().getWindow().getWidth();
		int height = Application::GetInstance().getWindow().getHeight();
		float ratio = ((width * 1.0f) / (height * 1.0f));
		
		projectionMatrix = glm::ortho(left * ratio, right * ratio, bottom, top, nearP, farP);

		this->left = left;
		this->right = right;
		this->bottom = bottom;
		this->top = top;
		this->nearP = nearP;
		this->farP = farP;
	}

	void OrthographicCamera::onWindowResize(unsigned width, unsigned height)
	{
		float ratio = ((width * 1.0f) / (height * 1.0f));
		projectionMatrix = glm::ortho(left * ratio, right * ratio, bottom, top, nearP, farP);
	}
}
