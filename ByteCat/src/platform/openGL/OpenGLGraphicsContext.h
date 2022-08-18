#pragma once
#ifdef BC_PLATFORM_PC
#include <GLFW/glfw3.h>
#include "byteCat/graphics/GraphicsContext.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLGraphicsContext : public Graphics::GraphicsContext
		{
		private:
			GLFWwindow* m_window;
			
		public:
			OpenGLGraphicsContext(GLFWwindow* window): m_window(window) {}
			
			void init(unsigned int windowWidth, unsigned int windowHeight) override;
			void swapBuffers() override;
		};
	}
}
#endif