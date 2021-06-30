#pragma once

#include "byteCat/Core.h"
#include "byteCat/input/events/Event.h"

namespace BC
{
	class BYTECAT_API Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}
	};
}