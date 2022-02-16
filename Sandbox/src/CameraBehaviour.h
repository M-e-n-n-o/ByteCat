#pragma once
#include <ByteCat.h>

#include "byteCat/utils/Time.h"
#include "glm/ext/matrix_clip_space.hpp"

using namespace BC;

class CameraBehaviour : public Behaviour
{
private:
	Transform* transform = nullptr;

	const float speed = 2;

public:
	void onAttach() override
	{
		transform = &m_coordinator->getComponent<Transform>(m_entity);
	}

	void onUpdate() override
	{		
		glm::vec3 movement = glm::vec3(0, 0, 0);

		if (Input::IsKeyPressed(KeyCode::W))
			movement.z += speed;

		if (Input::IsKeyPressed(KeyCode::S))
			movement.z -= speed;

		if (Input::IsKeyPressed(KeyCode::D))
			movement.x += speed;

		if (Input::IsKeyPressed(KeyCode::A))
			movement.x -= speed;

		if (Input::IsKeyPressed(KeyCode::Space))
			movement.y += speed;

		if (Input::IsKeyPressed(KeyCode::LeftShift))
			movement.y -= speed;

		auto mouseVelocity = (Input::GetMouseVelocity() * 0.1f);
		transform->rotation.x += mouseVelocity.y;
		transform->rotation.y += mouseVelocity.x;

		float dx = movement.z * glm::sin(glm::radians(transform->rotation.y));
		float dz = movement.z * glm::cos(glm::radians(transform->rotation.y));
		dx += movement.x * glm::sin(glm::radians(transform->rotation.y + 90));
		dz += movement.x * glm::cos(glm::radians(transform->rotation.y + 90));

		transform->position.x += (dx * Time::GetDeltaTime());
		transform->position.z += (dz * Time::GetDeltaTime());
		transform->position.y += (movement.y * Time::GetDeltaTime());
		
		auto& window = Application::GetInstance().getWindow();
		float aspect = (window.getWidth() * 1.0f) / (window.getHeight() * 1.0f);

		Renderer::SetSceneData({
				Math::CreateViewMatrix(transform->position, transform->rotation),
				glm::perspective(glm::radians(70.0f), aspect, 0.01f, 1000.0f) });
	}
};