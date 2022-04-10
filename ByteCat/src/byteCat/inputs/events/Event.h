#pragma once

#include "byteCat/utils/Macro.h"

namespace BC
{
	namespace Inputs
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
			None = 0,
			EventCatApplication = BIT(0),
			EventCatInput = BIT(1),
			EventCatKeyboard = BIT(2),
			EventCatMouse = BIT(3),
			EventCatMouseButton = BIT(4)
		};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }


		/// <summary>
		/// This class represents an Event (input) for a ByteCat application.
		/// </summary>
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

		/// <summary>
		/// Use this class to automatic handle events in the correct way.
		/// 
		/// Example:
		/// dispatcher.dispatch<<EventType>>(BC_BIND_EVENT_FN(<Function pointer>));
		/// </summary>
		class EventDispatcher
		{
		private:
			Event& m_event;

		public:
			EventDispatcher(Event& event) : m_event(event) {}

			// F will be deduced by the compiler
			template<class T, typename F>
			bool dispatch(const F& func)
			{
				if (m_event.getEventType() == T::getStaticType())
				{
					m_event.handled |= func(static_cast<T&>(m_event));
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
}