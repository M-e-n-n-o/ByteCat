#include "bcpch.h"
#include "byteCat/ecs/EntityManager.h"

namespace BC
{
	namespace Ecs
	{
		EntityManager::EntityManager()
		{
			for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				m_entities.push(entity);
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
				LOG_WARN("Given entity %d out of range", entity);
				return;
			}

			m_dependencies[entity].reset();

			m_names[entity] = nullptr;

			m_entities.push(entity);
			--m_entityCount;
		}

		const char* EntityManager::getName(const Entity& entity)
		{
			return m_names[entity];
		}

		void EntityManager::setDependencies(const Entity& entity, Dependencies dependencies)
		{
			if (entity > MAX_ENTITIES)
			{
				LOG_WARN("Given entity %d out of range", entity);
				return;
			}

			m_dependencies[entity] = dependencies;
		}

		Dependencies& EntityManager::getDependencies(const Entity& entity)
		{
			if (entity > MAX_ENTITIES)
			{
				LOG_WARN("Given entity %d out of range", entity);
			}

			return m_dependencies[entity];
		}
	}
}
