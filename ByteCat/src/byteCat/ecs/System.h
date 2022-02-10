#pragma once
#include <set>
#include "byteCat/ecs/Entity.h"

namespace BC
{
	class EcsCoordinator;

	class System
	{
	private:
		friend class SystemManager;
	
	protected:
		EcsCoordinator* m_coordinator;
		std::set<Entity> m_entities;
		
	public:
		virtual ~System() = default;

		virtual void onUpdate() = 0;
	};
}
