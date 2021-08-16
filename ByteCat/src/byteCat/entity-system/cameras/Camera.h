#pragma once

#include "byteCat/entity-system/GameObject.h"
#include "glm/mat4x4.hpp"

namespace BC
{
	/*
	 * Class Camera:
	 *		This class represents a generic camera in a ByteCat application.
	 *		Choose one of the derrived classes to get a specific camera.
	 */
	class Camera : public ObjectComponent
	{
	protected:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

		Camera() = default;
	public:
		virtual ~Camera() = default;

		// Gets called when the window is resized. Recalculate the projectionmatrix here.
		virtual void onWindowResize(unsigned int width, unsigned int height) = 0;
		
		glm::mat4& getProjectionMatrix() { return projectionMatrix; }
		glm::mat4& getViewMatrix() { calculateViewMatrix(); return viewMatrix; }

	protected:
		void calculateViewMatrix();
	};
}
