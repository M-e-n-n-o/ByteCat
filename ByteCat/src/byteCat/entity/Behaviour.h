#pragma once

namespace BC
{
	class Entity;
	
	class Behaviour
	{
	private:
		friend class Entity;
	
	protected:
		Entity* m_entity = nullptr;
	
	public:
		virtual ~Behaviour() = default;

		// Gets called when the behaviour gets attached to an entity
		virtual void onAttach() {}
		// Gets called every frame
		virtual void onUpdate() {}
		// Gets called when the behaviour is detached from an entity (not called when entity gets destroyed)
		virtual void onDetach() {}
	};
}
