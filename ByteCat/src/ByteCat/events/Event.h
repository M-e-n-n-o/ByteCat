#pragma once

#include "bcpch.h"
#include "byteCat/Core.h"

namespace BC
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None					= 0,
		EventCatApplication		= BIT(0),
		EventCatInput			= BIT(1),
		EventCatKeyboard		= BIT(2),
		EventCatMouse			= BIT(3),
		EventCatMouseButton		= BIT(4)
	};
	
	class Event
	{
	public:
		bool handled = false;
		
		virtual ~Event() = default;

		virtual EventType getEventType() const = 0;
		virtual int getCategoryFlags() const = 0;

		bool isInCategory(const EventCategory cat) const
		{
			return getCategoryFlags() & cat;
		}
	};
}