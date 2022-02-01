#pragma once
#include <vector>
#include "byteCat/entity/Behaviour.h"

namespace BC
{
	struct Component
	{
		virtual ~Component() = default;
	};	
	
	class Entity
	{
	private:
		std::string m_name;
		
		Entity* m_parent = nullptr;
		std::vector<Entity*> m_children;

		std::vector<Component*> m_components;

		Behaviour* m_behaviour = nullptr;

	public:
		Entity(const std::string& name);
		Entity(const std::string& name, Entity* parent);
		~Entity();

		void setName(const std::string name) { m_name = name; }

		void setParent(Entity* parent);
		void attachChild(Entity* child);
		void detachChild(Entity* entity);
		
		template<class T>
		T* addComponent();

		template<class T>
		T* getComponent();

		template<class T>
		void removeComponent();
		
		void setBehaviour(Behaviour* behaviour);
	};

	// ----------------------------------------------------------------------------------
	// --------------------- Template elaborations of Entity ----------------------------
	
	template <class T>
	T* Entity::addComponent()
	{
		T* component = new T();
		m_components.push_back(component);
		return component;
	}

	template <class T>
	T* Entity::getComponent()
	{
		for (auto component : m_components)
		{
			if (T* x = dynamic_cast<T*>(component))
			{
				return x;
			}
		}

		return nullptr;
	}

	template <class T>
	void Entity::removeComponent()
	{
		Component* toRemove = nullptr;
		
		int index = -1;
		for (int i = 0; i < m_components.size(); i++)
		{
			if (Component* x = dynamic_cast<T*>(m_components[i]))
			{
				index = i;
				toRemove = x;
				break;
			}
		}

		if (index == -1)
		{
			LOG_WARN("Entity \"{0}\" did not contain the component \"{1}\"", m_name, typeid(T).name());
			return;
		}

		m_components.erase(m_components.begin() + index);
		delete toRemove;
	}
}
