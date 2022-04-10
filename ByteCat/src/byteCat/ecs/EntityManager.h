#pragma once
#include <bitset>
#include <queue>
#include "byteCat/ecs/Entity.h"
#include "byteCat/ecs/Behaviour.h"

namespace BC
{
	namespace Ecs
	{
		class EntityManager
		{
		private:
			std::queue<Entity> m_entities;
			std::array<Dependencies, MAX_ENTITIES> m_dependencies;
			std::array<Behaviour*, MAX_ENTITIES> m_behaviours;
			std::array<const char*, MAX_ENTITIES> m_names;

			uint32_t m_entityCount = 0;

		public:
			EntityManager();

			Entity createEntity(const char* name);
			void destroyEntity(const Entity& entity);

			template<class T>
			void setBehaviour(const Entity& entity, EcsCoordinator* coordinator, const T& behaviour);

			Behaviour* getBehaviour(const Entity& entity);

			void updateBehaviours();

			const char* getName(const Entity& entity);

			void setDependencies(const Entity& entity, Dependencies dependencies);
			Dependencies& getDependencies(const Entity& entity);
		};

		template <class T>
		void EntityManager::setBehaviour(const Entity& entity, EcsCoordinator* coordinator, const T& behaviour)
		{
			if (entity > MAX_ENTITIES)
			{
				LOG_WARN("Given entity {0} out of range", entity);
				return;
			}

			if (m_behaviours[entity] != nullptr)
			{
				m_behaviours[entity]->onDetach();
				delete m_behaviours[entity];
				m_behaviours[entity] = nullptr;
			}

			Behaviour* newBehaviour = new T(behaviour);
			newBehaviour->m_entity = entity;
			newBehaviour->m_coordinator = coordinator;

			m_behaviours[entity] = newBehaviour;
			m_behaviours[entity]->onAttach();
		}
	}
}
