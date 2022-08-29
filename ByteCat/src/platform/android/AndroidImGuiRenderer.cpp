#ifdef BC_PLATFORM_ANDROID
#include "bcpch.h"
#include "platform/android/AndroidImGuiRenderer.h"

namespace BC
{
	namespace Platform
	{
		void AndroidImGuiRenderer::enable()
		{
			LOG_INFO("ImGui is disabled for now on Android");
		}

		void AndroidImGuiRenderer::disable()
		{

		}

		void AndroidImGuiRenderer::begin()
		{

		}

		void AndroidImGuiRenderer::end()
		{

		}
	}
}
#endif