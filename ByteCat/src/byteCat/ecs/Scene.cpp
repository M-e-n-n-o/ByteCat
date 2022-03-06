#include "bcpch.h"
#include "byteCat/ecs/Scene.h"
#include "byteCat/ecs/components/Mesh.h"
#include "byteCat/ecs/systems/RenderSubmitter.h"

namespace BC
{
	Scene::Scene(const std::string& name): m_name(name)
	{
		m_ecsCoordinator = std::make_shared<EcsCoordinator>();
	}

	void Scene::registerDefaultSystems()
	{
		m_ecsCoordinator->registerSystem<RenderSubmitter>();
		m_ecsCoordinator->registerSystem<CameraSystem>();
	}

	void Scene::onUpdate()
	{
		m_ecsCoordinator->updateBehaviours();
		m_ecsCoordinator->updateSystems();
	}

	Entity Scene::getMainCamera()
	{
		if (m_cameraSystem != nullptr)
		{
			return m_cameraSystem->getMainCamera();
		}

		return -1;
	}
}
