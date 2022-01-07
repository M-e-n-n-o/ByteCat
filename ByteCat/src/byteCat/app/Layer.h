#pragma once

#include "byteCat/input/events/Event.h"

namespace BC
{
	/// <summary>
	/// This class represents a layer in the application which will be updated (when enabled)
	/// every game loop when added to the LayerStack from the Application class.
	/// </summary>
	class Layer
	{
	private:
		std::string name;

	public:
		bool enabled = true;
	
	public:
		Layer(std::string name): name(name) {}
		virtual ~Layer() = default;

		// Gets called when attached to the layerstack
		virtual void onAttach() {}
		// Gets called when detached from the layerstack
		virtual void onDetach() {}
		// Gets called every game loop before the rendering
		virtual void onUpdate() {}
		// Gets called right before the rendering takes place
		virtual void onRender() {}
		// Gets called every time an event occurs in the application
		virtual void onEvent(Event& event) {}

		std::string getName() const { return name; }
	};
}