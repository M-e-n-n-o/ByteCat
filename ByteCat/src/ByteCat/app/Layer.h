#pragma once

#include "byteCat/input/events/Event.h"

namespace BC
{
	/*
	 * Class Layer:
	 *		This class represents a layer in the application which will be updated (when enabled)
	 *		every game loop when added to the LayerStack from the Application class.
	 */
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
		// Gets called every game loop after rendering the main game. Use this to render imGui windows
		virtual void onImGuiRender() {}
		// Gets called every time an event occurs in the application
		virtual void onEvent(Event& event) {}

		std::string getName() const { return name; }
	};
}