#pragma once
#include "byteCat/ecs/Entity.h"

namespace BC
{	
	class Behaviour
	{	
	protected:
		Entity m_entity;
	
	public:
		Behaviour() {}
		Behaviour(const Entity& entity): m_entity(entity) {}
		
		virtual ~Behaviour() = default;

		virtual void onUpdate(EcsCoordinator& coordinator) { LOG_INFO(m_entity); }
	};
}
