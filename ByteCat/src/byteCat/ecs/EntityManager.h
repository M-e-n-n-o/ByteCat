#pragma once
#include <bitset>
#include <queue>
#include "byteCat/ecs/Entity.h"

namespace BC
{
	namespace Ecs
	{
		class EntityManager
		{
		private:
			std::queue<Entity> m_entities;
			std::array<Dependencies, MAX_ENTITIES> m_dependencies;
			std::array<const char*, MAX_ENTITIES> m_names;

			uint32_t m_entityCount = 0;

		public:
			EntityManager();

			Entity createEntity(const char* name);
			void destroyEntity(const Entity& entity);

			const char* getName(const Entity& entity);

			void setDependencies(const Entity& entity, Dependencies dependencies);
			Dependencies& getDependencies(const Entity& entity);
		};
	}
}
