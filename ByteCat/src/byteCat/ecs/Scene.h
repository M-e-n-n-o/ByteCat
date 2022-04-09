#pragma once
#include <memory>
#include "byteCat/ecs/EcsCoordinator.h"
#include "byteCat/ecs/systems/CameraSystem.h"

namespace BC
{
	class Scene
	{
	private:
		std::string m_name;
		std::shared_ptr<EcsCoordinator> m_ecsCoordinator;

		std::shared_ptr<CameraSystem> m_cameraSystem;
	
	public:
		Scene(const std::string& name);

		void registerDefaultSystems();
		
		void onUpdate();

		Entity getMainCamera();
		
		std::string& getName() { return m_name; }
		std::shared_ptr<EcsCoordinator> getEcsCoordinator() const { return m_ecsCoordinator; }
	};
}