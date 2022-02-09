#pragma once
#include "byteCat/ecs/System.h"
#include "byteCat/ecs/EcsCoordinator.h"

namespace BC
{
	class BehaviourSystem : public System
	{		
	public:
		void update(EcsCoordinator& coordinator) override
		{			
			for (auto const& entity : m_entities)
			{				
				auto& behaviour = coordinator.getComponent<Behaviour>(entity);
				behaviour.onUpdate(coordinator);
			}
		}
	};
}
