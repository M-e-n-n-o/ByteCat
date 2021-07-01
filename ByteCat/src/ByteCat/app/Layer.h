#pragma once

#include "byteCat/Core.h"
#include "byteCat/input/events/Event.h"

namespace BC
{
	class Layer
	{
	private:
		std::string name;
		bool enabled = true;
	
	public:
		Layer(std::string name): name(name) {}
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		void enable(bool enabled) { this->enabled = enabled; }
		bool isEnabled() const { return enabled; }
		std::string getName() const { return name; }
	};
}