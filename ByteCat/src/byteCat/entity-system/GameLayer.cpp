#include "bcpch.h"
#include "byteCat/entity-system/GameLayer.h"
#include "byteCat/entity-system/cameras/Camera.h"

namespace BC
{
	void GameLayer::onUpdate()
	{
		for (std::shared_ptr<GameObject>& object : gameObjects)
		{
			if (object->isEnabled)
			{
				object->update();
			}
		}
	}

	void GameLayer::onWindowResize(unsigned width, unsigned height)
	{
		if (camera != nullptr)
		{
			camera->getComponent<Camera>()->onWindowResize(width, height);
		}
	}

	std::shared_ptr<GameObject> GameLayer::CreateGameObject(std::string name, Transform const& transform)
	{
		LOG_INFO("Creating a new GameObject: {0}", name);

		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name, transform);
		gameObjects.push_back(gameObject);
		return gameObject;
	}

	void GameLayer::RemoveGameObject(std::shared_ptr<GameObject>& toRemove)
	{
		LOG_INFO("Removing the GameObject: {0}", toRemove->name);

		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			if (*it == toRemove)
			{
				gameObjects.erase(it);
				return;
			}
		}
	}

	void GameLayer::SetCamera(std::shared_ptr<GameObject>& newCamera)
	{
		if (newCamera->hasComponent<Camera>())
		{
			camera = newCamera;
		} else
		{
			camera = nullptr;
			LOG_ERROR("Failed to set the camera object due to a missing camera component");
		}
	}
}
