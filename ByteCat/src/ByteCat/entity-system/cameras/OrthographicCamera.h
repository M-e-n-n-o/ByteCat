#pragma once

#include "byteCat/entity-system/cameras/Camera.h"

namespace BC
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float nearP, float farP);

		void setProjection(float left, float right, float bottom, float top, float nearP, float farP);
	};
}
