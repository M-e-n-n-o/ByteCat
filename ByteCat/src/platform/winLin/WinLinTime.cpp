#ifdef BC_PLATFORM_PC
#include "bcpch.h"
#include "byteCat/app/Time.h"
#include "GLFW/glfw3.h"

namespace BC
{
	namespace App
	{
		void Time::onUpdate()
		{
			const double currentTime = glfwGetTime();
			s_deltaTime = (currentTime - s_lastFrameTime);
			s_lastFrameTime = currentTime;
		}

		void Time::onEvent(Inputs::Event& event)
		{
			if (event.getEventType() == Inputs::EventType::WindowFocus)
			{
				s_lastFrameTime = glfwGetTime();
			}
		}
	}
}

#endif