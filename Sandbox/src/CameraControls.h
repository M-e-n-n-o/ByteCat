#pragma once

#include <ByteCat.h>

using namespace BC;


class CameraControls : public ObjectComponent
{
public:
	~CameraControls() = default;
	
	void onAttach()
	{
		
	}
	
	void onUpdate() override
	{
		const float speed = 15.0f;
		const float rotationSpeed = 60.0f;
		
		float currentSpeed = 0.0f;
		float currentRotationSpeed = 0.0f;
		
		if (Input::IsKeyPressed(KeyCode::W))
		{
			currentSpeed += speed;
		}

		if (Input::IsKeyPressed(KeyCode::S))
		{
			currentSpeed -= speed;
		}

		if (Input::IsKeyPressed(KeyCode::D))
		{
			currentRotationSpeed += rotationSpeed;
		}

		if (Input::IsKeyPressed(KeyCode::A))
		{
			currentRotationSpeed -= rotationSpeed;
		}

		if (Input::IsKeyPressed(KeyCode::Space))
		{
			gameObject->transform.position.y += speed * Application::GetDelta();
		}

		if (Input::IsKeyPressed(KeyCode::LeftControl))
		{
			gameObject->transform.position.y -= speed * Application::GetDelta();
		}

		gameObject->transform.rotation.y += (currentRotationSpeed * 1.0) * Application::GetDelta();
		
		float distance = currentSpeed * Application::GetDelta();
		float y = gameObject->transform.rotation.y;
		float dx = distance * glm::cos(glm::radians(y + 270));
		float dz = distance * glm::sin(glm::radians(y + 270));
		
		gameObject->transform.position.x += dx;
		gameObject->transform.position.z += dz;
	}
	
	void onDetach() override
	{
		
	}
};