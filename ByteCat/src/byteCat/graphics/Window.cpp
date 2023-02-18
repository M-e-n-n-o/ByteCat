#include "bcpch.h"
#include "byteCat/graphics/Window.h"

#ifdef BC_PLATFORM_PC
	#include "platform/winLin/WinLinWindow.h"
#elif defined(BC_PLATFORM_MOBILE)
	#include "platform/mobile/MobileWindow.h"
#endif

namespace BC
{
	namespace Graphics
	{		
		Window* Window::Create(const WindowSettings& settings, void* appInputData)
		{
#ifdef BC_PLATFORM_PC
			LOG_INFO("Detected Windows/Linux platform");
			return new Platform::WinLinWindow(settings);
#elif defined(BC_PLATFORM_MOBILE)
			LOG_INFO("Detected Mobile platform");
			return new Platform::MobileWindow(settings, appInputData);
#endif
		}
	}
}
