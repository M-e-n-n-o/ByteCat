#pragma once
#include <ByteCat.h>

using namespace BC;
using namespace App;
using namespace Inputs;

struct Spectator : Ecs::Component
{
	float speed;
	
	Spectator(float speed): speed(speed) {}
	virtual ~Spectator() = default;

	TYPE_NAME("Spectator")
};

class SpectatorSystem : public Ecs::System
{
public:
	
	void onUpdate() override
	{
		for (auto& entity : m_entities)
		{
			auto transform = m_coordinator->getComponent<Ecs::Transform>(entity);
			auto spectator = m_coordinator->getComponent<Spectator>(entity);

			glm::vec3 movement = glm::vec3(0, 0, 0);

			if (Input::IsPressed(KeyCode::W))
				movement.z += spectator->speed;

			if (Input::IsPressed(KeyCode::S))
				movement.z -= spectator->speed;

			if (Input::IsPressed(KeyCode::D))
				movement.x += spectator->speed;

			if (Input::IsPressed(KeyCode::A))
				movement.x -= spectator->speed;

			if (Input::IsPressed(KeyCode::Space))
				movement.y += spectator->speed;

			if (Input::IsPressed(KeyCode::LeftShift))
				movement.y -= spectator->speed;

			auto mouseVelocity = (Input::GetMouseVelocity() * 0.1f);
			transform->rotation.x += mouseVelocity.y;
			transform->rotation.y += mouseVelocity.x;

			float dx = movement.z * glm::cos(glm::radians(transform->rotation.y - 90));
			float dz = movement.z * glm::sin(glm::radians(transform->rotation.y - 90));
			dx += movement.x * glm::cos(glm::radians(transform->rotation.y));
			dz += movement.x * glm::sin(glm::radians(transform->rotation.y));

			transform->position.x += (dx * Time::GetDeltaTime());
			transform->position.z += (dz * Time::GetDeltaTime());
			transform->position.y += (movement.y * Time::GetDeltaTime());
		}
	}

	static Ecs::Dependencies GetDependencies(Ecs::EcsCoordinator* coordinator)
	{
		Ecs::Dependencies signature;
		signature.set(coordinator->getComponentType<Ecs::Transform>());
		signature.set(coordinator->getComponentType<Spectator>());
		return signature;
	}
};