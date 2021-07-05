#include "bcpch.h"
#include "byteCat/game-object/GameObject.h"

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
		for (auto it = components.begin(); it != components.end(); ++it)
		{			
			if ((*it)->equals(*toRemove))
			{
				(*it)->onDetach();
				components.erase(it);
				
				delete toRemove;
				toRemove = nullptr;
				return;
			}
		}
	}
}
