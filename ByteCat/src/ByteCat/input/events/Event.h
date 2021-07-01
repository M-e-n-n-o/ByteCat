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

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }
	
	class Event
	{
	public:
		bool handled = false;
		
		virtual ~Event() = default;

		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;

		bool isInCategory(const EventCategory cat) const
		{
			return getCategoryFlags() & cat;
		}
	};

	class EventDispatcher
	{
	private:
		Event& event;
		
	public:
		EventDispatcher(Event& event): event(event){}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool dispatch(const F& func)
		{
			if (event.getEventType() == T::getStaticType())
			{
				event.handled |= func(static_cast<T&>(event));
				return true;
			}
			return false;
		}
	};

	class EventListener
	{
	public:
		virtual ~EventListener() = default;
		virtual void onEvent(Event& event) = 0;
	};
}