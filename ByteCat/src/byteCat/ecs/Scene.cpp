#include "bcpch.h"
#include "byteCat/ecs/Scene.h"

#include "byteCat/ecs/components/Mesh.h"
#include "byteCat/ecs/components/Material.h"
#include "byteCat/ecs/components/Transform.h"
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
		Signature signature;
		signature.set(m_ecsCoordinator->getComponentType<Transform>());
		signature.set(m_ecsCoordinator->getComponentType<Mesh>());
		signature.set(m_ecsCoordinator->getComponentType<Material>());
		m_ecsCoordinator->setSystemSignature<RenderSubmitter>(signature);
	}

	void Scene::onUpdate()
	{
		m_ecsCoordinator->updateBehaviours();
		m_ecsCoordinator->updateSystems();
	}
}
