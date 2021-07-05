#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

namespace BC
{
	// This struct holds all the information about an entity
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform(): position({0, 0, 0}), rotation({ 0, 0, 0 }), scale({ 1, 1, 1 }) {}
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}
	};

	#define OBJ_COMP_RETURN_NAME std::string getName() override { return typeid(*this).name(); }

	// This class is used by the game objects as components of that object
	class ObjectComponent
	{
	private:
		std::string name;
		
	public:
		ObjectComponent(std::string const& name): name(name) {}
		virtual ~ObjectComponent() = default;

		virtual std::string getName() = 0;
		
		// Gets called when attached to a GameObject
		virtual void onAttach() {}
		// Gets called every frame
		virtual void onUpdate() {}
		// Gets called when the component gets removed from the GameObject
		virtual void onDetach() {}
		
		bool equals(const ObjectComponent& other) const
		{
			return name == other.name;
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

		glm::mat4 getModelMatrix();
		
		// This function returns the ObjectComponent with the given ObjectComponent type
		template<class T>
		T* getComponentOfType();
	};

	
	template <class T>
	T* GameObject::getComponentOfType()
	{
		for (ObjectComponent* component : components)
		{
			if (component->getName() == typeid(T).name())
			{
				return dynamic_cast<T*>(component);
			}
		}

		return nullptr;
	}
}
