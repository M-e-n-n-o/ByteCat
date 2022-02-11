#pragma once
#include <memory>
#include <unordered_map>
#include "byteCat/ecs/Entity.h"
#include "byteCat/ecs/ComponentArray.h"

namespace BC
{
	class ComponentManager
	{
	private:
		std::unordered_map<const char*, ComponentType> m_componentTypes;
		std::unordered_map<const char*, std::shared_ptr<BaseComponentArray>> m_componentArrays;
		
		ComponentType m_nextComponentType = 0;

	public:
		template<typename T>
		void registerComponent()
		{
			const char* typeName = typeid(T).name();	

			if (m_componentTypes.find(typeName) != m_componentTypes.end())
			{
				LOG_WARN("Cannot register the same componentType {0} multiple times", typeName);
				return;
			}

			m_componentTypes.insert({ typeName, m_nextComponentType });
			m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			++m_nextComponentType;
		}

		template<typename T>
		ComponentType& getComponentType()
		{
			const char* typeName = typeid(T).name();

			if (m_componentTypes.find(typeName) == m_componentTypes.end())
			{
				LOG_WARN("ComponentType {0} has not been registered yet", typeName);
			}

			return m_componentTypes[typeName];
		}

		template<typename T>
		void addComponent(const Entity& entity, const T& component)
		{
			getComponentArray<T>()->insertData(entity, component);
		}

		template<typename T>
		void removeComponent(const Entity& entity)
		{
			getComponentArray<T>()->removeData(entity);
		}

		template<typename T>
		T& getComponent(const Entity& entity)
		{
			return getComponentArray<T>()->getData(entity);
		}

		void entityDestroyed(const Entity& entity)
		{
			for (auto const& pair : m_componentArrays)
			{
				auto const& component = pair.second;
				component->entityDestroyed(entity);
			}
		}

	private:
		template<typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray()
		{
			const char* typeName = typeid(T).name();
			
			if (m_componentTypes.find(typeName) == m_componentTypes.end())
			{
				LOG_WARN("ComponentType {0} has not been registered yet", typeName);
				return nullptr;
			}

			return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
		}
	};
}
