#pragma once

#include <string>
#include "byteCat/inputs/events/Event.h"

namespace BC
{
	namespace Graphics
	{
		// This struct holds the settings for a window
		struct WindowSettings
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vSync;
		};

		/**
		 * @brief
		 * This class represents a window from a ByteCat application.
		 * A window will automatically be created by the Application class.
		 */
		class Window
		{
		public:
			Window() = default;
			virtual ~Window() = default;

			// Swap the buffers, poll the events
			virtual void update() const = 0;
			// Shutdown the window
			virtual void shutdown() const = 0;

			// Change the window settings to the new width and heigt
			virtual void resize(unsigned int width, unsigned int height) = 0;

			virtual std::string getTitle() const = 0;
			virtual unsigned int getWidth() const = 0;
			virtual unsigned int getHeight() const = 0;

			virtual void setVsync(bool enabled) = 0;
			virtual bool getVsync() const = 0;

			virtual bool isMinimized() = 0;

			virtual void captureMouse(bool capture) = 0;

			// Returns the native window
			virtual void* getNativeWindow() const = 0;

			// Sets the eventlistener of the incoming events
			virtual void setEventListener(Inputs::EventListener* newListener) = 0;

			static Window* Create(const WindowSettings& setting);
		};
	}
}
