#pragma once

#include "byteCat/inputs/events/Event.h"
#include "glm/vec2.hpp"

namespace BC
{
	namespace Inputs
	{
		class TouchEvent : public Event
		{
		private:
			glm::vec2 position;

		protected:
			TouchEvent(const glm::vec2& position): position(position) {}
			virtual ~TouchEvent() = default;

		public:
			glm::vec2 getPosition() const { return position; }
			int getCategoryFlags() const override { return EventCatInput | EventCatTouch; }
		};
		
		class TouchHoverEvent : public TouchEvent
		{
		public:
			TouchHoverEvent(const glm::vec2& position): TouchEvent(position) {}

			EVENT_CLASS_TYPE(TouchHover)
		};

		class TouchBeganEvent : public TouchEvent
		{
		public:
			TouchBeganEvent(const glm::vec2& position) : TouchEvent(position) {}

			EVENT_CLASS_TYPE(TouchBegan)
		};

		class TouchMovedEvent : public TouchEvent
		{
		public:
			TouchMovedEvent(const glm::vec2& position) : TouchEvent(position) {}

			EVENT_CLASS_TYPE(TouchMoved)
		};

		class TouchEndedEvent : public TouchEvent
		{
		public:
			TouchEndedEvent(const glm::vec2& position) : TouchEvent(position) {}

			EVENT_CLASS_TYPE(TouchEnded)
		};

		class TouchCancelledEvent : public TouchEvent
		{
		public:
			TouchCancelledEvent(const glm::vec2& position) : TouchEvent(position) {}

			EVENT_CLASS_TYPE(TouchCancelled)
		};
	}
}
