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
			//const char* typeName = typeid(T).name();
			
			const bool isComponent = std::is_base_of<Component, T>::value;
			if (!isComponent)
			{
				const char* typeName = typeid(T).name();
				LOG_WARN("{0} cannot be registered as a component, it is not derrived of Component", typeName);
				return;
			}

			const char* typeName = T::getTypeName();

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
		ComponentType& getComponentType(bool autoRegister)
		{
			//const char* typeName = typeid(T).name();

			const bool isComponent = std::is_base_of<Component, T>::value;
			if (!isComponent)
			{
				const char* typeName = typeid(T).name();
				LOG_WARN("Cannot get componentType {0}, it is not derrived of Component", typeName);
			}

			const char* typeName = T::getTypeName();
			

			if (m_componentTypes.find(typeName) == m_componentTypes.end())
			{
				LOG_WARN("ComponentType {0} has not been registered yet", typeName);

				if (autoRegister)
				{
					LOG_INFO("Auto registering ComponentType {0}", typeName);
					registerComponent<T>();
				}
			}

			return m_componentTypes[typeName];
		}

		template<typename T>
		void addComponent(const Entity& entity, const T& component)
		{
			getComponentArray<T>(true)->insertData(entity, component);
		}

		template<typename T>
		void removeComponent(const Entity& entity)
		{
			getComponentArray<T>(false)->removeData(entity);
		}

		template<typename T>
		T& getComponent(const Entity& entity)
		{
			return getComponentArray<T>(false)->getData(entity);
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
		std::shared_ptr<ComponentArray<T>> getComponentArray(bool autoRegister)
		{
			//const char* typeName = typeid(T).name();

			const bool isComponent = std::is_base_of<Component, T>::value;
			if (!isComponent)
			{
				const char* typeName = typeid(T).name();
				LOG_WARN("Cannot get componentArray of componentType {0}, it is not derrived of Component", typeName);
				return nullptr;
			}

			const char* typeName = T::getTypeName();
			
			if (m_componentTypes.find(typeName) == m_componentTypes.end())
			{
				LOG_WARN("ComponentType {0} has not been registered yet", typeName);

				if (!autoRegister)
				{
					return nullptr;
				}

				LOG_INFO("Auto registering ComponentType {0}", typeName);
				registerComponent<T>();
			}

			return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
		}
	};
}
