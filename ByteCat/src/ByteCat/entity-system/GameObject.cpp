#include "bcpch.h"
#include <typeindex>
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
		if (RenderComponent* x = dynamic_cast<RenderComponent*>(component))
		{
			if (getComponentOfType<RenderComponent>() != nullptr)
			{
				LOG_WARN("A gameobject, {0}, can only have 1 RenderComponent", name);
				delete component;
				return;
			}
		}
		
		components.push_back(component);
		component->gameObject = this;
		component->onAttach();
	}

	void GameObject::removeComponent(ObjectComponent* toRemove)
	{
		if (toRemove == nullptr)
		{
			return;
		}

		int iterator = 0;
		for (ObjectComponent* component : components)
		{
			if (typeid(*component) == typeid(*toRemove))
			{
				LOG_INFO("Removed object component {0}", typeid(*toRemove).name());
				component->onDetach();
				components.erase(components.begin() + iterator);
		
				delete component;
				toRemove = nullptr;
				return;
			}
		
			iterator++;
		}
	}

	glm::mat4 GameObject::getModelMatrix() const
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, transform.position);
		matrix = glm::rotate(matrix, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
		matrix = glm::scale(matrix, transform.scale);
		return matrix;
	}
}
