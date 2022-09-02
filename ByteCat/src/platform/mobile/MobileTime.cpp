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
			s_deltaTime = (currentTime - s_lastFrameTime);
			s_lastFrameTime = currentTime;
		}

		void Time::onEvent(Inputs::Event& event)
		{
			if (event.getEventType() == Inputs::EventType::WindowFocus)
			{
				s_lastFrameTime = glfmGetTime();
			}
		}
	}
}

#endif