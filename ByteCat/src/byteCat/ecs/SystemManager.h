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
		std::unordered_map<const char*, Signature> m_signatures;
		std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};

	public:
		template<typename T>
		std::shared_ptr<T> registerSystem()
		{
			const char* typeName = typeid(T).name();

			if (m_systems.find(typeName) != m_systems.end())
			{
				LOG_WARN("Cannot register system {0} more then once", typeName);
			}

			auto system = std::make_shared<T>();
			m_systems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void setSignature(const Signature& signature)
		{
			const char* typeName = typeid(T).name();

			if (m_systems.find(typeName) == m_systems.end())
			{
				LOG_WARN("System {0} is not registered yet", typeName);
			}

			m_signatures.insert({ typeName, signature });
		}

		void entityDestroyed(const Entity& entity)
		{
			for (auto const& pair : m_systems)
			{
				auto const& system = pair.second;
				system->m_entities.erase(entity);
			}
		}

		void entitySignatureChanged(const Entity& entity, Signature entitySignature)
		{
			for (auto const& pair : m_systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = m_signatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->m_entities.insert(entity);
				} else
				{
					system->m_entities.erase(entity);
				}
			}
		}

		void updateSystems(EcsCoordinator& coordinator)
		{
			for (auto const& pair : m_systems)
			{
				auto const& system = pair.second;
				
				system->update(coordinator);
			}
		}
	};
}
