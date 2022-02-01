#include "bcpch.h"
#include "byteCat/entity/Entity.h"

namespace BC
{
	Entity::Entity(const std::string& name): m_name(name) {}

	Entity::Entity(const std::string& name, Entity* parent)
	{
		m_name = name;

		if (parent == nullptr)
		{
			LOG_WARN("Given parent of \"{0}\" is null", m_name);
		} else
		{
			m_parent = parent;
		}
	}


	Entity::~Entity()
	{
		if (m_parent != nullptr)
		{
			m_parent->detachChild(this);
		}

		delete m_behaviour;
		while (!m_children.empty()) delete m_children.back(), m_children.pop_back();
		while (!m_components.empty()) delete m_components.back(), m_components.pop_back();
	}

	void Entity::setParent(Entity* parent)
	{
		if (m_parent != nullptr)
		{
			m_parent->detachChild(this);
		}
		
		m_parent = parent;
		
		if (m_parent != nullptr)
		{
			m_parent->attachChild(this);
		}
	}

	void Entity::attachChild(Entity* child)
	{
		if (child == nullptr)
		{
			LOG_WARN("Cannot attach child from \"{0}\", child is null", m_name);
			return;
		}
		
		m_children.push_back(child);
	}

	void Entity::detachChild(Entity* entity)
	{
		if (entity == nullptr)
		{
			LOG_WARN("Cannot detach child from \"{0}\", child is null", m_name);
			return;
		}
		
		int index = -1;
		for (int i = 0; i < m_children.size(); i++)
		{
			if (m_children[i] == entity)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
		{
			m_children.erase(m_children.begin() + index);
		}
		else
		{
			LOG_WARN("Cannot detach child from \"{0}\", child \"{1}\" is not registered as one of its children", m_name, entity->m_name);
		}
	}

	void Entity::setBehaviour(Behaviour* behaviour)
	{
		if (behaviour == nullptr)
		{
			return;
		}

		m_behaviour->onDetach();
		delete m_behaviour;
		
		m_behaviour = behaviour;
		m_behaviour->m_entity = this;
		m_behaviour->onAttach();
	}
}
