// ReSharper disable All
#pragma once

#include "byteCat/input/events/Event.h"

namespace BC
{
	class WindowResizeEvent : public Event
	{
	private:
		unsigned int width;
		unsigned int height;

	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

		unsigned int getWidth() const { return width; }
		unsigned int getHeight() const { return height; }

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