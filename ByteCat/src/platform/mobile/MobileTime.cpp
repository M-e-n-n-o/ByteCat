#ifdef BC_PLATFORM_MOBILE
#include "bcpch.h"
#include <glfm.h>
#include "byteCat/app/Time.h"

namespace BC
{
	namespace App
	{
		void Time::onUpdate()
		{
			double currentTime = glfmGetTime();
			static double lastFrameTime = 0;
			s_deltaTime = (currentTime - lastFrameTime);
			lastFrameTime = currentTime;
		}
	}
}

#endif