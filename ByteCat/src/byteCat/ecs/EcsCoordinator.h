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

		Entity createEntity(const char* name)
		{
			return m_entityManager->createEntity(name);
		}

		void destroyEntity(const Entity& entity)
		{
			m_entityManager->destroyEntity(entity);
			m_componentManager->entityDestroyed(entity);
			m_systemManager->entityDestroyed(entity);
		}

		template<class T>
		void setBehaviour(const Entity& entity, const T& behaviour)
		{
			m_entityManager->setBehaviour<T>(entity, this, behaviour);
		}

		Behaviour* getBehaviour(const Entity& entity)
		{
			return m_entityManager->getBehaviour(entity);
		}

		void updateBehaviours()
		{
			m_entityManager->updateBehaviours();
		}

		const char* getEntityName(const Entity& entity)
		{
			return m_entityManager->getName(entity);
		}

		template<typename T>
		void registerComponent()
		{
			m_componentManager->registerComponent<T>();
		}

		// This method will automatically register the component if it hasnt been yet
		template<typename T>
		void addComponent(const Entity& entity, const T& component)
		{			
			m_componentManager->addComponent<T>(entity, component);

			auto signature = m_entityManager->getDependencies(entity);
			signature.set(m_componentManager->getComponentType<T>(false), true);
			m_entityManager->setDependencies(entity, signature);

			m_systemManager->entitySignatureChanged(entity, signature);
		}

		template<typename T>
		void removeComponent(const Entity& entity)
		{
			m_componentManager->removeComponent<T>(entity);

			auto dependencies = m_entityManager->getDependencies(entity);
			dependencies.set(m_componentManager->getComponentType<T>(false), false);
			m_entityManager->setDependencies(entity, dependencies);

			m_systemManager->entitySignatureChanged(entity, dependencies);
		}

		template<typename T>
		T* getComponent(const Entity& entity)
		{
			return m_componentManager->getComponent<T>(entity);
		}

		// This method will automatically register the component if it hasnt been yet
		template<typename T>
		ComponentType& getComponentType()
		{
			return m_componentManager->getComponentType<T>(true);
		}

		template<typename T>
		std::shared_ptr<T> registerSystem()
		{
			auto system = m_systemManager->registerSystem<T>(this);

			Dependencies dependencies = T::GetDependencies(this);
			m_systemManager->setDependencies<T>(dependencies);
			
			return system;
		}

		void updateSystems()
		{
			m_systemManager->updateSystems();
		}
	};
}