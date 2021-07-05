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


	
	class GameComponent
	{
	private:
		std::string name;
		
	public:
		GameComponent(std::string const& name): name(name) {}
		virtual ~GameComponent() = default;

		// Gets called when attached to a GameObject
		virtual void onStart() {}
		// Gets called every frame
		virtual void onUpdate() {}
		// Gets called when the GameObject this component is attached to, gets deleted or the component gets removed from the GameObject
		virtual void onDestroy() {}

		bool equals(const std::string& otherName) const
		{
			return name == otherName;
		}
	};
	
	
	class GameObject
	{
	protected:
		Transform transform;

		std::vector<GameComponent*> components;
	
	public:
		GameObject(Transform const& transform): transform(transform) {}
		virtual ~GameObject();

		void update();
		
		//Transform getRelativeTransform() const;
		Transform& getTransform() { return transform; }

		void addComponent(GameComponent* component);
		void removeComponent(std::string const& componentName);
			
	public:
		static std::shared_ptr<GameObject> Create(Transform const& transform = Transform())
		{
			return std::make_shared<GameObject>(transform);
		}
	};
}
