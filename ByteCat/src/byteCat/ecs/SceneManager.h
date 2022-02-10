#pragma once
#include "byteCat/ecs/Scene.h"

namespace BC
{
	class SceneManager
	{
	private:
		inline static int s_activeScene = -1;
		inline static std::vector<std::shared_ptr<Scene>> s_scenes;

	public:
		static std::shared_ptr<Scene> CreateScene(const std::string& name);
		static void ActivateScene(std::shared_ptr<Scene> scene);
		static void RemoveScene(std::shared_ptr<Scene> scene);

		static std::shared_ptr<Scene> GetScene(const std::string& name);
		static std::shared_ptr<Scene> GetActiveScene();
	};
}
