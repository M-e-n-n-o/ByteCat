#include "bcpch.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "platform/openGL/OpenGLGraphicsContext.h"

namespace BC
{
	namespace Platform
	{
		void OpenGLGraphicsContext::init(unsigned int windowWidth, unsigned int windowHeight)
		{
			LOG_INFO("Adding OpenGL context to window");
			
			glfwMakeContextCurrent(m_window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				LOG_CRITICAL("Failed to initialize glad");
				std::exit(-1);
			}

			LOG_INFO("OpenGL Renderer Info:");
			LOG_INFO("   Vendor:   {0}", glGetString(GL_VENDOR));
			LOG_INFO("   Renderer: {0}", glGetString(GL_RENDERER));
			LOG_INFO("   Version:  {0}", glGetString(GL_VERSION));

			if (GLVersion.major < 4 || (GLVersion.major == 4 && GLVersion.minor < 5))
			{
				LOG_CRITICAL("ByteCat requires at least OpenGL version 4.5");
				std::exit(-1);
			}
		}

		void OpenGLGraphicsContext::swapBuffers()
		{
			glfwSwapBuffers(m_window);
		}
	}
}
