#include "bcpch.h"
#include "byteCat/entity-system/GameObjectLayer.h"
#include "byteCat/entity-system/cameras/Camera.h"

namespace BC
{
	void GameObjectLayer::onUpdate()
	{
		for (std::shared_ptr<GameObject>& object : gameObjects)
		{
			if (object->isEnabled)
			{
				object->update();
			}
		}
	}

	std::shared_ptr<GameObject> GameObjectLayer::CreateGameObject(Transform const& transform)
	{
		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(transform);
		gameObjects.push_back(gameObject);
		return gameObject;
	}

	void GameObjectLayer::RemoveGameObject(std::shared_ptr<GameObject>& toRemove)
	{
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			if (*it == toRemove)
			{
				gameObjects.erase(it);
				return;
			}
		}
	}

	void GameObjectLayer::SetCamera(std::shared_ptr<GameObject>& newCamera)
	{
		if (newCamera->getComponentOfType<Camera>())
		{
			camera = newCamera;
		} else
		{
			camera = nullptr;
			LOG_ERROR("Failed to set the camera object due to a missing camera component");
		}
	}
}
