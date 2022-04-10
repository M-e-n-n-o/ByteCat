#include "bcpch.h"
#include "byteCat/ecs/Scene.h"

namespace BC
{
	namespace Ecs
	{
		Scene::Scene(const std::string& name) : m_name(name)
		{
			m_ecsCoordinator = std::make_shared<EcsCoordinator>();
		}

		void Scene::onUpdate()
		{
			m_ecsCoordinator->updateBehaviours();
			m_ecsCoordinator->updateSystems();
		}
	}
}
