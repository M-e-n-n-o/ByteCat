#pragma once

#include <string>
#include "byteCat/events/Event.h"

namespace BC
{
	struct WindowSetting
	{
		std::string title;
		int width;
		int height;
		bool vSync;
	};

	
	class Window
	{
	protected:
		EventListener* listener;
		WindowSetting setting;
		
	public:
		virtual ~Window() = default;

		virtual void update() = 0;
		virtual void shutdown() = 0;
		
		std::string getTitle() const { return setting.title; }
		int getWidth() const { return setting.width; }
		int getHeight() const { return setting.height; }
		
		virtual void setVsync(bool enabled) = 0;
		bool getVsync() const { return setting.vSync; }

		virtual void* getNativeWindow() const = 0;
		
		void setEventListener(EventListener* newListener) { listener = newListener; }
		EventListener* getEventListener() const { return listener; }
		
		static Window* Create(WindowSetting& windowSetting);
	};
}
