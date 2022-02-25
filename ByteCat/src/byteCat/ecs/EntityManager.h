#pragma once
#include <bitset>
#include <queue>
#include "byteCat/ecs/Entity.h"
#include "byteCat/ecs/Behaviour.h"

namespace BC
{	
	class EntityManager
	{
	private:
		std::queue<Entity> m_entities;
		std::array<Dependencies, MAX_ENTITIES> m_signatures;
		std::array<Behaviour*, MAX_ENTITIES> m_behaviours;
		std::array<const char*, MAX_ENTITIES> m_names;

		uint32_t m_entityCount = 0;
	
	public:
		EntityManager();

		Entity& createEntity(const char* name);
		void destroyEntity(const Entity& entity);

		template<typename T, typename... Args>
		void setBehaviour(const Entity& entity, EcsCoordinator* coordinator, Args&... args);

		void updateBehaviours();

		const char* getName(const Entity& entity);

		void setSignature(const Entity& entity, Dependencies signature);
		Dependencies& getSignature(const Entity& entity);
	};

	template <typename T, typename ... Args>
	void EntityManager::setBehaviour(const Entity& entity, EcsCoordinator* coordinator, Args&... args)
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

		Behaviour* behaviour = new T(args...);
		behaviour->m_entity = entity;
		behaviour->m_coordinator = coordinator;
		
		m_behaviours[entity] = behaviour;
		m_behaviours[entity]->onAttach();
	}
}
