#include "bcpch.h"
#include "byteCat/app/Window.h"

#ifdef BC_PLATFORM_WINDOWS
	#include "platform/windows/WindowsWindow.h"
#endif

namespace BC
{
	Window* Window::Create(WindowSettings& setting)
	{
		#ifdef BC_PLATFORM_WINDOWS
			LOG_INFO("Detected Windows platform");
			return new Platform::WindowsWindow(setting);
		#else
			LOG_CRITICAL("Platform not supported yet :(");
		#endif
	}
}
