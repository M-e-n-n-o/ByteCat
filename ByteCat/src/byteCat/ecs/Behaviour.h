#pragma once
#include "byteCat/ecs/Entity.h"

namespace BC
{
	class EcsCoordinator;
	
	class Behaviour
	{	
	protected:
		Entity m_entity;
	
	public:
		Behaviour(const Entity& entity): m_entity(entity) {}
		
		virtual ~Behaviour() = default;

		virtual void onAttach() {}
		virtual void onUpdate(EcsCoordinator& coordinator) {}
		virtual void onDetach() {}
	};
}
