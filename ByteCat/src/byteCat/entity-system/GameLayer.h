#pragma once

#include <memory>
#include "byteCat/entity-system/GameObject.h"
#include "byteCat/app/Layer.h"

namespace BC
{
	/*
	 * Class GameLayer:
	 *		This layer holds all the data of a scene. This layer also updates a scene.
	 *		Use this class to create new GameObjects or to destroy existing ones.
	 */
	class GameLayer : public Layer
	{
		inline static std::shared_ptr<GameObject> camera;
		inline static std::vector<std::shared_ptr<GameObject>> gameObjects;
		
	public:
		GameLayer(): Layer("GameLayer") {}
		~GameLayer() = default;
		
		void onUpdate() override;
		void onWindowResize(unsigned int width, unsigned int height);

		// Call this method to create a new GameObject
		static std::shared_ptr<GameObject> CreateGameObject(std::string name, Transform const& transform = Transform());
		// Call this method to remove a GameObject
		static void RemoveGameObject(std::shared_ptr<GameObject>& toRemove);

		// Call this function to set the camera of the Application
		static void SetCamera(std::shared_ptr<GameObject>& newCamera);
		std::shared_ptr<GameObject>& GetCamera() { return camera; }
		
		std::vector<std::shared_ptr<GameObject>>& getGameObjects() { return gameObjects; }
	};
}
