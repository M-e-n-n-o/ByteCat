#include "bcpch.h"
#include "byteCat/entity-system/GameObject.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	GameObject::~GameObject()
	{
		for (ObjectComponent* component : components)
		{
			delete component;
		}
	}

	void GameObject::update()
	{
		for (ObjectComponent* component : components)
		{
			component->onUpdate();
		}
	}

	void GameObject::addComponent(ObjectComponent* component)
	{
		components.push_back(component);
		component->onAttach();
	}

	void GameObject::removeComponent(ObjectComponent* toRemove)
	{
		if (toRemove == nullptr)
		{
			return;
		}
		
		for (auto it = components.begin(); it != components.end(); ++it)
		{			
			if ((*it)->equals(*toRemove))
			{
				LOG_INFO("removed");
				(*it)->onDetach();
				components.erase(it);
				
				delete toRemove;
				toRemove = nullptr;
				return;
			}
		}
	}

	glm::mat4 GameObject::getModelMatrix()
	{
		return Utils::CreateModelMatrix(transform.position, transform.rotation, transform.scale);
	}
}
