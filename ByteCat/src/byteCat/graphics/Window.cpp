#include "bcpch.h"
#include "byteCat/graphics/Window.h"

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
	#include "platform/winLin/WinLinWindow.h"
#elif defined(BC_PLATFORM_ANDROID)
	#include "platform/android/AndroidWindow.h"
#endif

namespace BC
{
	namespace Graphics
	{
		Window* Window::Create(const WindowSettings& setting, void* appInputData)
		{
#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
			LOG_INFO("Detected Windows/Linux platform");
			return new Platform::WinLinWindow(setting);
#elif defined(BC_PLATFORM_ANDROID)
			LOG_INFO("Detected Android platform");
			return new Platform::AndroidWindow(appInputData);
#else
			LOG_CRITICAL("Platform not supported/detected :(");
			return nullptr;
#endif
		}
	}
}
