#pragma once
#include <memory>
#include "byteCat/ecs/EcsCoordinator.h"

namespace BC
{
	class Scene
	{
	private:
		std::string m_name;
		std::shared_ptr<EcsCoordinator> m_ecsCoordinator;

	public:
		Scene(const std::string& name);

		void registerDefaultSystems();
		
		void onUpdate();
		
		std::string& getName() { return m_name; }
		std::shared_ptr<EcsCoordinator> getEcsCoordinator() const { return m_ecsCoordinator; }
	};
}
