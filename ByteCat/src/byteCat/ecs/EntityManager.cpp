#include "bcpch.h"
#include "byteCat/ecs/EntityManager.h"

namespace BC
{
	EntityManager::EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			m_entities.push(entity);
		}
	}

	Entity& EntityManager::createEntity()
	{
		if (m_entityCount >= MAX_ENTITIES)
		{
			LOG_WARN("Max entitiy count reached");
		}

		Entity id = m_entities.front();
		m_entities.pop();
		++m_entityCount;

		return id;
	}

	void EntityManager::destroyEntity(const Entity& entity)
	{
		if (entity > MAX_ENTITIES)
		{
			LOG_WARN("Given entity {0} out of range", entity);
		}

		m_signatures[entity].reset();

		m_entities.push(entity);
		--m_entityCount;
	}

	void EntityManager::setSignature(const Entity& entity, Signature signature)
	{
		if (entity > MAX_ENTITIES)
		{
			LOG_WARN("Given entity {0} out of range", entity);
		}

		m_signatures[entity] = signature;
	}

	Signature& EntityManager::getSignature(const Entity& entity)
	{
		if (entity > MAX_ENTITIES)
		{
			LOG_WARN("Given entity {0} out of range", entity);
		}

		return m_signatures[entity];
	}
}
