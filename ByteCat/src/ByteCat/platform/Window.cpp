#include "bcpch.h"
#include "byteCat/platform/Window.h"
#include "windows/WindowsWindow.h"

namespace BC
{
	Window* Window::Create(WindowSetting& windowSetting)
	{
	#ifdef BC_PLATFORM_WINDOWS
		return new WindowsWindow(windowSetting);
	#else
		BC_CRITICAL("Unknown platform");
		return nullptr;
	#endif
	}
}
