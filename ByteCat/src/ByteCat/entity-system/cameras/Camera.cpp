#include "bcpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "byteCat/entity-system/cameras/Camera.h"

namespace BC
{
	void Camera::calculateViewMatrix()
	{
		const Transform& t = gameObject->getTransform();
		
		viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::rotate(viewMatrix, glm::radians(t.rotation.x), glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(t.rotation.y), glm::vec3(0, 1, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(t.rotation.z), glm::vec3(0, 0, 1));
		const glm::vec3 negativePos = glm::vec3(-t.position.x, -t.position.y, -t.position.z);
		viewMatrix = glm::translate(viewMatrix, negativePos);
	}
}
