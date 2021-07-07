#pragma once
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
		
		// Gets called when attached to a GameObject
		virtual void onAttach() {}
		// Gets called every frame
		virtual void onUpdate() {}
		// Gets called when the component gets removed from the GameObject
		virtual void onDetach() {}
	};
	

	/*
	 * Class GameObject:
	 *		This class represents a 3D/2D object in 3D/2D space.
	 */
	class GameObject
	{
	public:
		bool isEnabled = true;

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

		// This function returns the ObjectComponent with the given ObjectComponent type
		template<class T>
		T* getComponentOfType();

		// This function removes the ObjectComponent with the given ObjectComponent type
		template<class T>
		void removeComponent() { removeComponent(getComponentOfType<T>()); }

		glm::mat4 getModelMatrix() const;
	};

	
	// ---------------------------------------------------------------------------
	// ---------- Template elaborations of GameObject ----------------------------

	template <class T>
	T* GameObject::getComponentOfType()
	{
		for (ObjectComponent* component : components)
		{
			if (T* x = dynamic_cast<T*>(component))
			{
				return x;
			}
		}

		return nullptr;
	}

	
}
