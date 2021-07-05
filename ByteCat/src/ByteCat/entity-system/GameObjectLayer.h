#pragma once

#include <memory>
#include "byteCat/entity-system/GameObject.h"
#include "byteCat/app/Layer.h"

namespace BC
{
	class GameObjectLayer : public Layer
	{
	private:
		inline static std::vector<std::shared_ptr<GameObject>> gameObjects;
		
	public:
		GameObjectLayer(): Layer("GameObjectLayer") {}
		~GameObjectLayer() = default;
		
		void onUpdate() override;

		static std::shared_ptr<GameObject> CreateGameObject(Transform const& transform = Transform());		
		static void RemoveGameObject(std::shared_ptr<GameObject>& toRemove);
	};
}
