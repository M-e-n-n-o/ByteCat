#pragma once

#include <memory>
#include "byteCat/entity-system/GameObject.h"
#include "byteCat/app/Layer.h"

namespace BC
{
	class GameLayer : public Layer
	{
		inline static std::shared_ptr<GameObject> camera;
		inline static std::vector<std::shared_ptr<GameObject>> gameObjects;
		
	public:
		GameLayer(): Layer("GameLayer") {}
		~GameLayer() = default;
		
		void onUpdate() override;

		static std::shared_ptr<GameObject> CreateGameObject(std::string name, Transform const& transform = Transform());		
		static void RemoveGameObject(std::shared_ptr<GameObject>& toRemove);

		static void SetCamera(std::shared_ptr<GameObject>& newCamera);
		std::shared_ptr<GameObject>& GetCamera() { return camera; }
		
		std::vector<std::shared_ptr<GameObject>>& getGameObjects() { return gameObjects; }
	};
}
