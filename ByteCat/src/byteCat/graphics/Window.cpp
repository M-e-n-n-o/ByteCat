#include "bcpch.h"
#include "byteCat/graphics/Window.h"

#ifdef BC_PLATFORM_PC
	#include "platform/winLin/WinLinWindow.h"
#elif defined(BC_PLATFORM_MOBILE)
	#include "platform/android/AndroidWindow.h"
#endif

namespace BC
{
	namespace Graphics
	{
		Window* Window::Create(const WindowSettings& setting, void* appInputData)
		{
#ifdef BC_PLATFORM_PC
			LOG_INFO("Detected Windows/Linux platform");
			return new Platform::WinLinWindow(setting);
#elif defined(BC_PLATFORM_MOBILE)
			LOG_INFO("Detected Android platform");
			return new Platform::AndroidWindow(appInputData);
#else
			LOG_CRITICAL("Platform not supported/detected :(");
			return nullptr;
#endif
		}
	}
}
