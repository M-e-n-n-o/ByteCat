#pragma once

#include "byteCat/graphics/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLGraphicsContext : public GraphicsContext
		{
		private:
			GLFWwindow* window;
			
		public:
			OpenGLGraphicsContext(GLFWwindow* window): window(window) {}
			
			void init() override;
			void swapBuffers() override;
		};
	}
}
