#pragma once

#include "byteCat/input/events/Event.h"
#include "byteCat/input/MouseCodes.h"

namespace BC
{
	class MouseMovedEvent : public Event
	{
	private:
		float mouseX;
		float mouseY;

	public:
		MouseMovedEvent(const float x, const float y) : mouseX(x), mouseY(y) {}

		float getMouseX() const { return mouseX; }
		float getMouseY() const { return mouseY; }

		EVENT_CLASS_TYPE(MouseMoved)
		int getCategoryFlags() const override { return EventCatMouse | EventCatInput; }
	};


	class MouseScrolledEvent : public Event
	{
	private:
		float offsetX;
		float offsetY;

	public:
		MouseScrolledEvent(const float x, const float y) : offsetX(x), offsetY(y) {}

		float getOffsetX() const { return offsetX; }
		float getOffsetY() const { return offsetY; }

		EVENT_CLASS_TYPE(MouseScrolled)
		int getCategoryFlags() const override { return EventCatMouse | EventCatInput; }
	};


	class MouseButtonEvent : public Event
	{
	protected:
		MouseCode mouseCode;

		MouseButtonEvent(const MouseCode mouseCode) : mouseCode(mouseCode) {}

	public:
		MouseCode getMouseButton() const { return mouseCode; }
		
		int getCategoryFlags() const override { return EventCatMouse | EventCatInput | EventCatMouseButton; }
	};


	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};


	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
