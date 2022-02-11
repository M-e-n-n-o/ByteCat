#pragma once
#include <memory>
#include "byteCat/ecs/EntityManager.h"
#include "byteCat/ecs/ComponentManager.h"
#include "byteCat/ecs/SystemManager.h"

namespace BC
{
	class EcsCoordinator
	{
	private:
		std::unique_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<SystemManager> m_systemManager;

	public:
		EcsCoordinator()
		{
			m_componentManager = std::make_unique<ComponentManager>();
			m_entityManager = std::make_unique<EntityManager>();
			m_systemManager = std::make_unique<SystemManager>();
		}

		Entity& createEntity(const char* name)
		{
			return m_entityManager->createEntity(name);
		}

		void destroyEntity(const Entity& entity)
		{
			m_entityManager->destroyEntity(entity);
			m_componentManager->entityDestroyed(entity);
			m_systemManager->entityDestroyed(entity);
		}

		template<typename T, typename... Args>
		void setBehaviour(const Entity& entity, Args&... args)
		{
			m_entityManager->setBehaviour<T>(entity, this, args...);
		}

		void updateBehaviours()
		{
			m_entityManager->updateBehaviours();
		}

		const char* getEntityName(const Entity& entity)
		{
			return m_entityManager->getName(entity);
		}

		void updateSystems()
		{
			m_systemManager->updateSystems();
		}

		template<typename T>
		void registerComponent()
		{
			m_componentManager->registerComponent<T>();
		}

		template<typename T>
		void addComponent(const Entity& entity, const T& component)
		{
			m_componentManager->addComponent<T>(entity, component);

			auto signature = m_entityManager->getSignature(entity);
			signature.set(m_componentManager->getComponentType<T>(), true);
			m_entityManager->setSignature(entity, signature);

			m_systemManager->entitySignatureChanged(entity, signature);
		}

		template<typename T>
		void removeComponent(const Entity& entity)
		{
			m_componentManager->removeComponent<T>(entity);

			auto signature = m_entityManager->getSignature(entity);
			signature.set(m_componentManager->getComponentType<T>(), false);
			m_entityManager->setSignature(entity, signature);

			m_systemManager->entitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& getComponent(const Entity& entity)
		{
			return m_componentManager->getComponent<T>(entity);
		}

		template<typename T>
		ComponentType& getComponentType()
		{
			return m_componentManager->getComponentType<T>();
		}

		template<typename T>
		std::shared_ptr<T> registerSystem()
		{
			return m_systemManager->registerSystem<T>(this);
		}

		template<typename T>
		void setSystemSignature(Signature signature)
		{
			m_systemManager->setSignature<T>(signature);
		}
	};
}
