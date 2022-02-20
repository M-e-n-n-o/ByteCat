#include "bcpch.h"
#include "byteCat/ecs/Scene.h"

#include "byteCat/ecs/components/Mesh.h"
#include "byteCat/ecs/components/Material.h"
#include "byteCat/ecs/components/Transform.h"
#include "byteCat/ecs/components/Camera.h"

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
		Signature signatureRenderSubmitter;
		signatureRenderSubmitter.set(m_ecsCoordinator->getComponentType<Transform>());
		signatureRenderSubmitter.set(m_ecsCoordinator->getComponentType<Mesh>());
		signatureRenderSubmitter.set(m_ecsCoordinator->getComponentType<Material>());
		m_ecsCoordinator->setSystemSignature<RenderSubmitter>(signatureRenderSubmitter);

		m_cameraSystem = m_ecsCoordinator->registerSystem<CameraSystem>();
		Signature signatureCameraSystem;
		signatureCameraSystem.set(m_ecsCoordinator->getComponentType<Transform>());
		signatureCameraSystem.set(m_ecsCoordinator->getComponentType<Camera>());
		m_ecsCoordinator->setSystemSignature<CameraSystem>(signatureCameraSystem);
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
