#pragma once
#include "byteCat/app/Layer.h"
#include "byteCat/ecs/Scene.h"

namespace BC
{
	namespace Ecs
	{
		class SceneManager : public App::Layer
		{
		private:
			inline static int s_activeScene = -1;
			inline static std::vector<std::shared_ptr<Scene>> s_scenes;

		public:
			SceneManager() : Layer("SceneManager") {}

			static std::shared_ptr<Scene> CreateScene(const std::string& name);
			static void ActivateScene(std::shared_ptr<Scene> scene);
			static void RemoveScene(std::shared_ptr<Scene> scene);

			void onUpdate() override;

			static std::shared_ptr<Scene> GetScene(const std::string& name);
			static std::shared_ptr<Scene> GetActiveScene();
		};
	}
}
