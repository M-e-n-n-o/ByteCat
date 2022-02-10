#pragma once
#include "byteCat/ecs/Entity.h"

namespace BC
{
	class EcsCoordinator;
	
	class Behaviour
	{
	private:
		friend class EntityManager;
	
	protected:
		EcsCoordinator* m_coordinator;
		Entity m_entity = -1;
	
	public:		
		virtual ~Behaviour() = default;

		virtual void onAttach() {}
		virtual void onUpdate() {}
		virtual void onDetach() {}
	};
}
