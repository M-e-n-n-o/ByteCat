#ifdef BC_PLATFORM_MOBILE
#include "bcpch.h"
#include <glfm.h>
#include "platform/android/AndroidWindow.h"

namespace BC
{	
	namespace Platform
	{
		AndroidWindow::AndroidWindow(void* display)
		{
			LOG_INFO("Trying to initialize the Android window");

			/*
			 * Zorgen dat je met de WindowSettings hiervoor de opties kan invullen
			 */
			glfmSetDisplayConfig((GLFMDisplay*) display, )
		}

		AndroidWindow::~AndroidWindow()
		{
		}

		void AndroidWindow::update() const
		{
		}

		void AndroidWindow::shutdown() const
		{
		}

		void AndroidWindow::resize(unsigned width, unsigned height)
		{
		}

		std::string AndroidWindow::getTitle() const
		{
		}

		unsigned AndroidWindow::getWidth() const
		{
		}

		unsigned AndroidWindow::getHeight() const
		{
		}

		void AndroidWindow::setVsync(bool enabled)
		{
		}

		bool AndroidWindow::getVsync() const
		{
		}

		bool AndroidWindow::isMinimized()
		{
		}

		void AndroidWindow::captureMouse(bool capture)
		{
		}

		void* AndroidWindow::getNativeWindow() const
		{
		}

		void AndroidWindow::setEventListener(Inputs::EventListener* newListener)
		{
		}
	}
}

#endif