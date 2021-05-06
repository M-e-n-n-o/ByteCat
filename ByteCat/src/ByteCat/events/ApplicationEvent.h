#pragma once

#include "byteCat/events/Event.h"

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
		
		EventType getEventType() const override { return EventType::WindowResize; }
		int getCategoryFlags() const override { return EventCatApplication; }
	};

	
	class WindowCloseEvent : public Event
	{
	public:
		EventType getEventType() const override { return EventType::WindowClose; }
		int getCategoryFlags() const override { return EventCatApplication; }
	};
}