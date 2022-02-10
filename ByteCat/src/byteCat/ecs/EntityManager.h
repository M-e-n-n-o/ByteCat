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
		std::array<Signature, MAX_ENTITIES> m_signatures;
		std::array<Behaviour*, MAX_ENTITIES> m_behaviours;

		uint32_t m_entityCount = 0;
	
	public:
		EntityManager();

		Entity& createEntity();
		void destroyEntity(const Entity& entity);

		template<typename T, typename... Args>
		void setBehaviour(const Entity& entity, Args&... args);

		void updateBehaviours(EcsCoordinator& coordinator);

		void setSignature(const Entity& entity, Signature signature);
		Signature& getSignature(const Entity& entity);
	};

	template <typename T, typename ... Args>
	void EntityManager::setBehaviour(const Entity& entity, Args&... args)
	{
		if (entity > MAX_ENTITIES)
		{
			LOG_WARN("Given entity {0} out of range", entity);
		}

		if (m_behaviours[entity] != nullptr)
		{			
			m_behaviours[entity]->onDetach();
			delete m_behaviours[entity];
			m_behaviours[entity] = nullptr;
		}

		Behaviour* behaviour = new T(args...);
		behaviour->m_entity = entity;
		
		m_behaviours[entity] = behaviour;
		m_behaviours[entity]->onAttach();
	}
}
