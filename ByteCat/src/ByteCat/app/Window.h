#pragma once

#include <string>
#include "byteCat/input/events/Event.h"

namespace BC
{
	/*
	 * Struct WindowSetting:
	 *		This struct holds the settings for a window
	 */
	struct WindowSetting
	{
		std::string title;
		int width;
		int height;
		bool vSync;
	};


	/*
	 * Class Window:
	 *		This class represents a window from a ByteCat application
	 */
	class Window
	{
	private:
		EventListener* listener;
		WindowSetting setting;
	
	public:
		Window(WindowSetting& windowSetting);
		~Window() { shutdown(); }

		// Swap the buffers, poll the events and update delta
		double update() const;
		// Shutdown the window
		void shutdown() const;

		// Change the window settings to the new width and heigt
		void resize(unsigned int width, unsigned int height);
		
		std::string getTitle() const { return setting.title; }
		int getWidth() const { return setting.width; }
		int getHeight() const { return setting.height; }
		
		void setVsync(bool enabled);
		bool getVsync() const { return setting.vSync; }

		// Returns an OpenGL GLFWwindow
		void* getNativeWindow() const;

		// Sets the eventlistener of the incoming events
		void setEventListener(EventListener* newListener) { listener = newListener; }
		EventListener* getEventListener() const { return listener; }

		static std::unique_ptr<Window> Create(WindowSetting& windowSetting)
		{
			return std::make_unique<Window>(windowSetting);
		}
	};
}
