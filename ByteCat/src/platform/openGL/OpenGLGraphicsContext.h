#pragma once
#include <GLFW/glfw3.h>
#include "byteCat/graphics/GraphicsContext.h"

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
			
			void init(unsigned int windowWidth, unsigned int windowHeight) override;
			void swapBuffers() override;
		};
	}
}
