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
		component->gameObject = this;
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
				toRemove->gameObject = nullptr;
				toRemove = nullptr;
				return;
			}
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
		//
		// return Utils::CreateModelMatrix(transform.position, transform.rotation, transform.scale);
	}
}
