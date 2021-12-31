#include "bcpch.h"
#include "byteCat/app/Window.h"

#ifdef BC_PLATFORM_WINDOWS || BC_PLATFORM_LINUX
	#include "platform/winLin/WinLinWindow.h"
#endif

namespace BC
{
	Window* Window::Create(WindowSettings& setting)
	{
		#ifdef BC_PLATFORM_WINDOWS || BC_PLATFORM_LINUX
			LOG_INFO("Detected Windows/Linux platform");
			return new Platform::WinLinWindow(setting);
		#else
			LOG_CRITICAL("Platform not supported yet :(");
		#endif
	}
}
