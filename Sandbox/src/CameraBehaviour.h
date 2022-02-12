#pragma once
#include <ByteCat.h>

#include "glm/ext/matrix_clip_space.hpp"

using namespace BC;

class CameraBehaviour : public Behaviour
{
private:
	Transform* transform = nullptr;
	
public:
	void onAttach() override
	{
		transform = &m_coordinator->getComponent<Transform>(m_entity);
	}

	void onUpdate() override
	{		
		glm::vec3 movement = glm::vec3(0, 0, 0);

		if (Input::IsKeyPressed(KeyCode::W))
			movement.z += 0.01f;

		if (Input::IsKeyPressed(KeyCode::S))
			movement.z -= 0.01f;

		if (Input::IsKeyPressed(KeyCode::D))
			movement.x += 0.01f;

		if (Input::IsKeyPressed(KeyCode::A))
			movement.x -= 0.01f;

		if (Input::IsKeyPressed(KeyCode::Space))
			movement.y += 0.01f;

		if (Input::IsKeyPressed(KeyCode::LeftShift))
			movement.y -= 0.01f;

		auto mouseVelocity = (Input::GetMouseVelocity() * 0.1f);
		transform->rotation.x += mouseVelocity.y;
		transform->rotation.y += mouseVelocity.x;

		float dx = movement.z * glm::sin(glm::radians(transform->rotation.y));
		float dz = movement.z * glm::cos(glm::radians(transform->rotation.y));
		dx += movement.x * glm::sin(glm::radians(transform->rotation.y + 90));
		dz += movement.x * glm::cos(glm::radians(transform->rotation.y + 90));

		transform->position.x += dx;
		transform->position.z += dz;
		transform->position.y += movement.y;

		auto& window = Application::GetInstance().getWindow();
		float aspect = (window.getWidth() * 1.0f) / (window.getHeight() * 1.0f);

		Renderer::SetSceneData({
				Math::CreateViewMatrix(transform->position, transform->rotation),
				glm::perspective(glm::radians(70.0f), aspect, 0.01f, 1000.0f) });
	}
};