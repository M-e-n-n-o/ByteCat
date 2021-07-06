#pragma once

#include "byteCat/entity-system/cameras/Camera.h"

namespace BC
{
	class PerspectiveCamera: public Camera
	{
	public:
		PerspectiveCamera(float fov, float nearPlane, float farPlane);

		void setPerspective(float fov, float nearPlane, float farPlane);
	};
}
