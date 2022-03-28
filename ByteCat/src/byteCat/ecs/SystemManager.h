#pragma once
#include <memory>
#include <unordered_map>
#include "byteCat/ecs/Entity.h"
#include "byteCat/ecs/System.h"

namespace BC
{
	class SystemManager
	{
	private:
		std::unordered_map<const char*, Dependencies> m_dependencies;
		std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};

	public:
		template<typename T>
		std::shared_ptr<T> registerSystem(EcsCoordinator* coordinator)
		{
			const char* typeName = typeid(T).name();

			if (m_systems.find(typeName) != m_systems.end())
			{
				LOG_WARN("Cannot register system {0} more then once", typeName);
				return nullptr;
			}

			auto system = std::make_shared<T>();
			system->m_coordinator = coordinator;
			m_systems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void setDependencies(const Dependencies& dependencies)
		{
			const char* typeName = typeid(T).name();

			if (m_systems.find(typeName) == m_systems.end())
			{
				LOG_WARN("System {0} is not registered yet", typeName);
				return;
			}

			m_dependencies.insert({ typeName, dependencies });
		}

		void entityDestroyed(const Entity& entity)
		{
			for (auto const& pair : m_systems)
			{
				auto const& system = pair.second;
				system->m_entities.erase(entity);
			}
		}

		void entitySignatureChanged(const Entity& entity, Dependencies entityDependencies)
		{
			for (auto const& pair : m_systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemDependencies = m_dependencies[type];

				if ((entityDependencies & systemDependencies) == systemDependencies)
				{
					system->m_entities.insert(entity);
				} else
				{
					system->m_entities.erase(entity);
				}
			}
		}

		void updateSystems()
		{
			for (auto const& pair : m_systems)
			{
				auto const& system = pair.second;
				
				system->onUpdate();
			}
		}
	};
}
