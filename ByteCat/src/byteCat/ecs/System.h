#pragma once
#include <set>
#include "byteCat/ecs/Entity.h"

namespace BC
{
	class EcsCoordinator;

	class System
	{
	public:
		std::set<Entity> m_entities;

		virtual ~System() = default;

		virtual void update(EcsCoordinator& coordinator) = 0;
	};
}
