#pragma once

#include "byteCat/entity-system/cameras/Camera.h"

namespace BC
{
	class PerspectiveCamera: public Camera
	{
	private:
		float fov;
		float nearPlane;
		float farPlane;
		
	public:
		PerspectiveCamera(float fov, float nearPlane, float farPlane);

		void setPerspective(float fov, float nearPlane, float farPlane);

		void onWindowResize(unsigned width, unsigned height) override;
	};
}
