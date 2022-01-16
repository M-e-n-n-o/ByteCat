#pragma once

#include "byteCat/input/events/m_event.h"
#include "byteCat/input/MouseCodes.h"

namespace BC
{
	class MouseMovedEvent : public Event
	{
	private:
		float m_mouseX;
		float m_mouseY;

	public:
		MouseMovedEvent(const float x, const float y) : m_mouseX(x), m_mouseY(y) {}

		float getMouseX() const { return m_mouseX; }
		float getMouseY() const { return m_mouseY; }

		EVENT_CLASS_TYPE(MouseMoved)
		int getCategoryFlags() const override { return EventCatMouse | EventCatInput; }
	};


	class MouseScrolledEvent : public Event
	{
	private:
		float m_offsetX;
		float m_offsetY;

	public:
		MouseScrolledEvent(const float x, const float y) : m_offsetX(x), m_offsetY(y) {}

		float getOffsetX() const { return m_offsetX; }
		float getOffsetY() const { return m_offsetY; }

		EVENT_CLASS_TYPE(MouseScrolled)
		int getCategoryFlags() const override { return EventCatMouse | EventCatInput; }
	};


	class MouseButtonEvent : public Event
	{
	protected:
		MouseCode m_mouseCode;

		MouseButtonEvent(const MouseCode mouseCode) : m_mouseCode(mouseCode) {}

	public:
		MouseCode getMouseButton() const { return m_mouseCode; }
		
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
