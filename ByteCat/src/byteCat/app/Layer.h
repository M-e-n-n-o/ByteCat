#pragma once

#include "byteCat/input/events/m_event.h"

namespace BC
{
	/// <summary>
	/// This class represents a layer in the application which will be updated (when enabled)
	/// every game loop when added to the LayerStack from the Application class.
	/// </summary>
	class Layer
	{
	private:
		std::string m_name;

	public:
		bool m_enabled = true;
	
	public:
		Layer(std::string name): m_name(name) {}
		virtual ~Layer() = default;

		// Gets called when attached to the layerstack
		virtual void onAttach() {}
		// Gets called when detached from the layerstack
		virtual void onDetach() {}
		// Gets called every game loop before the rendering
		virtual void onUpdate() {}
		// Gets called right before the rendering takes place
		virtual void onRender() {}
		// Gets called after the rendering takes place
		virtual void onRenderComplete() {}
		// Gets called every time an event occurs in the application
		virtual void onEvent(Event& event) {}

		std::string getName() const { return m_name; }
	};
}