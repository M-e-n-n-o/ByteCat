#include "bcpch.h"
#include "byteCat/game-object/GameObjectLayer.h"

namespace BC
{
	void GameObjectLayer::onUpdate()
	{
		for (std::shared_ptr<GameObject>& object : gameObjects)
		{
			object->update();
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
				LOG_INFO("Removed a game object");
				gameObjects.erase(it);
				
				return;
			}
		}
	}
}
