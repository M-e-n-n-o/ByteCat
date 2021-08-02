#pragma once

#include "byteCat/entity-system/GameObject.h"
#include "glm/mat4x4.hpp"

namespace BC
{	
	class Camera : public ObjectComponent
	{
	protected:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

		Camera() = default;
	public:
		virtual ~Camera() = default;

		virtual void onWindowResize(unsigned int width, unsigned int height) = 0;
		
		glm::mat4& getProjectionMatrix() { return projectionMatrix; }
		glm::mat4& getViewMatrix() { calculateViewMatrix(); return viewMatrix; }

	protected:
		void calculateViewMatrix();
	};
}
