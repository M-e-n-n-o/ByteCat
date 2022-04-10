#include "bcpch.h"
#include "byteCat/graphics/Window.h"

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
	#include "platform/winLin/WinLinWindow.h"
#endif

namespace BC
{
	Window* Window::Create(const WindowSettings& setting)
	{
		#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
			LOG_INFO("Detected Windows/Linux platform");
			return new Platform::WinLinWindow(setting);
		#else
			LOG_CRITICAL("Platform not supported yet :(");
		#endif
	}
}
