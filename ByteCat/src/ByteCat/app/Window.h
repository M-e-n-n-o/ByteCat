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
	private:
		EventListener* listener;
		WindowSetting setting;
		
	public:
		Window(WindowSetting& windowSetting);
		~Window() { shutdown(); }

		void update() const;
		void shutdown() const;
		
		std::string getTitle() const { return setting.title; }
		int getWidth() const { return setting.width; }
		int getHeight() const { return setting.height; }
		
		void setVsync(bool enabled);
		bool getVsync() const { return setting.vSync; }

		void* getNativeWindow() const;
		
		void setEventListener(EventListener* newListener) { listener = newListener; }
		EventListener* getEventListener() const { return listener; }
	};
}
