#pragma once
#include <string>
#include <typeindex>
#include <vector>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

namespace BC
{
	class GameObject;

	// This struct holds all the information about an entity
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform(): position({0, 0, 0}), rotation({ 0, 0, 0 }), scale({ 1, 1, 1 }) {}
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}
	};


	// Place this macro in a derrived class from ObjectComponent
	#define OBJ_COMP_TYPE std::type_index getType() const override { return typeid(*this); }

	
	// This class is used by the game objects as components of that object
	class ObjectComponent
	{
	private:
		friend class GameObject;
	
	protected:
		GameObject* gameObject;
	
	public:
		ObjectComponent() = default;
		virtual ~ObjectComponent() = default;

		virtual std::type_index getType() const = 0;
		
		// Gets called when attached to a GameObject
		virtual void onAttach() {}
		// Gets called every frame
		virtual void onUpdate() {}
		// Gets called when the component gets removed from the GameObject
		virtual void onDetach() {}
		
		bool equals(const ObjectComponent& other) const
		{
			return getType() == other.getType();
		}
	};
	

	/*
	 * Class GameObject:
	 *		This class represents a 3D/2D object in 3D/2D space.
	 */
	class GameObject
	{
	protected:
		Transform transform;

		std::vector<ObjectComponent*> components;
	
	public:
		GameObject(Transform const& transform = Transform()): transform(transform) {}
		virtual ~GameObject();

		void update();
		
		Transform& getTransform() { return transform; }

		void addComponent(ObjectComponent* component);
		void removeComponent(ObjectComponent* toRemove);

		glm::mat4 getModelMatrix() const;
		
		// This function returns the ObjectComponent with the given ObjectComponent type
		template<class T>
		T* getComponentOfType();
	};

	
	template <class T>
	T* GameObject::getComponentOfType()
	{
		for (ObjectComponent* component : components)
		{
			if (component->getType() == typeid(T))
			{
				return dynamic_cast<T*>(component);
			}
		}

		return nullptr;
	}
}
