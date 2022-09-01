// ReSharper disable All
#pragma once

#include "byteCat/inputs/events/Event.h"

namespace BC
{
	namespace Inputs
	{
		class WindowCreatedEvent : public Event
		{
		public:
			EVENT_CLASS_TYPE(WindowCreated)

				int getCategoryFlags() const override { return EventCatApplication; }
		};

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

		class WindowRenderEvent : public Event
		{
		public:
			EVENT_CLASS_TYPE(WindowRender)
			
				int getCategoryFlags() const override { return EventCatApplication; }
		};

		class WindowOnFocusEvent : public Event
		{
		public:
			EVENT_CLASS_TYPE(WindowFocus)

				int getCategoryFlags() const override { return EventCatApplication; }
		};

		class WindowLostFocusEvent : public Event
		{
		public:
			EVENT_CLASS_TYPE(WindowLostFocus)

				int getCategoryFlags() const override { return EventCatApplication; }
		};
	}
}