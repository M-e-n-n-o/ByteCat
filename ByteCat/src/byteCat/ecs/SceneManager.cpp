#include "bcpch.h"
#include "byteCat/ecs/SceneManager.h"

namespace BC
{
	std::shared_ptr<Scene> SceneManager::CreateScene(const std::string& name)
	{
		auto scene = std::make_shared<Scene>(name);
		s_scenes.push_back(scene);
		return scene;
	}

	void SceneManager::ActivateScene(std::shared_ptr<Scene> scene)
	{
		for (int i = 0; i < s_scenes.size(); i++)
		{
			if (s_scenes[i] == scene)
			{
				s_activeScene = i;
				return;
			}
		}
	}

	void SceneManager::RemoveScene(std::shared_ptr<Scene> scene)
	{
		for (int i = 0; i < s_scenes.size(); i++)
		{
			if (s_scenes[i] == scene)
			{
				s_scenes.erase(s_scenes.begin() + i);				
				return;
			}
		}
	}

	std::shared_ptr<Scene> SceneManager::GetScene(const std::string& name)
	{
		for (int i = 0; i < s_scenes.size(); i++)
		{
			if (s_scenes[i]->getName() == name)
			{
				return s_scenes[i];
			}
		}

		return nullptr;
	}
}
