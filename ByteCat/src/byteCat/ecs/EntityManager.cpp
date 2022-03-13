#include "bcpch.h"
#include "byteCat/ecs/EntityManager.h"

namespace BC
{
	EntityManager::EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			m_entities.push(entity);
			m_behaviours[entity] = nullptr;
			m_names[entity] = nullptr;
		}
	}

	Entity EntityManager::createEntity(const char* name)
	{
		if (m_entityCount >= MAX_ENTITIES)
		{
			LOG_WARN("Max entitiy count reached");
			
			Entity id = -1;
			return id;
		}

		Entity id = m_entities.front();
		m_entities.pop();

		m_names[m_entityCount] = name;
		
		++m_entityCount;

		return id;
	}

	void EntityManager::destroyEntity(const Entity& entity)
	{
		if (entity > MAX_ENTITIES)
		{
			LOG_WARN("Given entity {0} out of range", entity);
			return;
		}

		m_signatures[entity].reset();
		
		delete m_behaviours[entity];
		m_behaviours[entity] = nullptr;

		m_names[entity] = nullptr;

		m_entities.push(entity);
		--m_entityCount;
	}

	Behaviour* EntityManager::getBehaviour(const Entity& entity)
	{
		return m_behaviours[entity];
	}

	void EntityManager::updateBehaviours()
	{
		for (int entity = 0; entity < MAX_ENTITIES; entity++)
		{
			auto behaviour = m_behaviours[entity];
			if (behaviour != nullptr)
			{
				if (behaviour->m_enabled)
				{
					behaviour->onUpdate();
				}
			}
		}
	}

	const char* EntityManager::getName(const Entity& entity)
	{
		return m_names[entity];
	}

	void EntityManager::setSignature(const Entity& entity, Dependencies signature)
	{
		if (entity > MAX_ENTITIES)
		{
			LOG_WARN("Given entity {0} out of range", entity);
			return;
		}

		m_signatures[entity] = signature;
	}

	Dependencies& EntityManager::getSignature(const Entity& entity)
	{
		if (entity > MAX_ENTITIES)
		{
			LOG_WARN("Given entity {0} out of range", entity);
		}

		return m_signatures[entity];
	}
}
