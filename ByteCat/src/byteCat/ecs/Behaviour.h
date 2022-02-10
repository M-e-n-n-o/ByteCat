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
		Entity m_entity = -1;
	
	public:		
		virtual ~Behaviour() = default;

		virtual void onAttach() {}
		virtual void onUpdate(EcsCoordinator& coordinator) {}
		virtual void onDetach() {}
	};
}
