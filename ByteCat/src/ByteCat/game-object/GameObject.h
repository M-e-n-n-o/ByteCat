#pragma once
#include <memory>
#include <vector>
#include "glm/vec3.hpp"

namespace BC
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform(): position({0, 0, 0}), rotation({ 0, 0, 0 }), scale({ 0, 0, 0 }) {}
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}
	};


	
	class ObjectComponent
	{
	private:
		std::string name;
		
	public:
		ObjectComponent(std::string const& name): name(name) {}
		virtual ~ObjectComponent() = default;

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

		template<class T>
		ObjectComponent* getComponentOfType();
	};

	
	template <class T>
	ObjectComponent* GameObject::getComponentOfType()
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (dynamic_cast<T*>(components[i]) != nullptr)
			{
				return components[i];
			}
		}

		return nullptr;
	}
}
