#pragma once
#include "byteCat/ecs/Entity.h"

namespace BC
{
	class BaseComponentArray
	{
	public:
		virtual ~BaseComponentArray() = default;
		virtual void entityDestroyed(const Entity& entity) = 0;
	};

	template<typename T>
	class ComponentArray : public BaseComponentArray
	{
	private:
		std::array<T, MAX_ENTITIES> m_componentArray;
		std::unordered_map<Entity, int> m_entityToIndexMap;
		std::unordered_map<int, Entity> m_indexToEntityMap;

		int m_size = 0;
	
	public:		
		void insertData(const Entity& entity, const T& component)
		{
			if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
			{
				LOG_WARN("Cannot add component {0} to entity {1} more than once", T::getTypeName(), entity);
				return;
			}

			int newIndex = m_size;
			m_entityToIndexMap[entity] = newIndex;
			m_indexToEntityMap[newIndex] = entity;
			m_componentArray[newIndex] = component;
			++m_size;
		}
		
		void removeData(const Entity& entity)
		{
			if (m_entityToIndexMap.find(entity) == m_entityToIndexMap.end())
			{
				LOG_WARN("Cannot remove non-existent component in entity {0}", entity);
				return;
			}

			int indexOfRemovedEntity = m_entityToIndexMap[entity];
			int indexOfLastElement = m_size - 1;
			m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

			Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
			m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			m_entityToIndexMap.erase(entity);
			m_indexToEntityMap.erase(indexOfLastElement);

			--m_size;
		}
		
		T& getData(const Entity& entity)
		{
			if (m_entityToIndexMap.find(entity) == m_entityToIndexMap.end())
			{
				LOG_WARN("Cannot retrieve non-existent component from entity {0}", entity);
			}

			return m_componentArray[m_entityToIndexMap[entity]];
		}

		void entityDestroyed(const Entity& entity) override
		{
			if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
			{
				removeData(entity);
			}
		}
	};
}
