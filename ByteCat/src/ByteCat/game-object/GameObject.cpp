#include "bcpch.h"
#include "byteCat/game-object/GameObject.h"

namespace BC
{
	GameObject::~GameObject()
	{
		for (GameComponent* component : components)
		{
			component->onDestroy();
			delete component;
		}
	}

	void GameObject::update()
	{
		for (GameComponent* component : components)
		{
			component->onUpdate();
		}
	}

	void GameObject::addComponent(GameComponent* component)
	{
		components.push_back(component);
		component->onStart();
	}

	void GameObject::removeComponent(std::string const& componentName)
	{
		for (GameComponent* component : components)
		{
			if (component->equals(componentName))
			{
				component->onDestroy();
				delete component;
				component = nullptr;
			}
		}

		components.erase(std::remove(components.begin(), components.end(), nullptr), components.end());
	}
}
