// ReSharper disable All
#pragma once

#include "byteCat/input/events/m_event.h"

namespace BC
{
	class WindowResizeEvent : public Event
	{
	private:
		unsigned int m_width;
		unsigned int m_height;

	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

		EVENT_CLASS_TYPE(WindowResize)
		
		int getCategoryFlags() const override { return EventCatApplication; }
	};

	
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(WindowClose)
		
		int getCategoryFlags() const override { return EventCatApplication; }
	};
}