#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
#include "bcpch.h"
#include "platform/openGL/OpenGLRendererAPI.h"

#if defined(BC_PLATFORM_PC)
	#include <glad/glad.h>
#elif defined(BC_PLATFORM_MOBILE)
	#include <glfm.h>
#endif

namespace BC
{
	namespace Platform
	{
		//#if defined(BC_PLATFORM_PC)
		    //void APIENTRY OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
			void OpenGLMessageCallback (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
			{
				switch (severity)
				{
				case GL_DEBUG_SEVERITY_HIGH:         LOG_CRITICAL("OpenGL high severity message:");	LOG_CRITICAL(message); return;
				case GL_DEBUG_SEVERITY_MEDIUM:       LOG_ERROR("OpenGL medium severity message: %s", message); return;
				case GL_DEBUG_SEVERITY_LOW:          LOG_WARN("OpenGL low severity message: %s", message); return;
				case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_WARN("OpenGL notification message: %s", message); return;
				}

				LOG_ERROR("Unknown OpenGL message severity level!");
			}
		//#endif
		
		OpenGLRendererAPI::OpenGLRendererAPI()
		{
			#if defined(BC_ENABLE_LOG)
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(OpenGLMessageCallback, nullptr);

				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
			#endif

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

		void OpenGLRendererAPI::setViewport(unsigned x, unsigned y, unsigned width, unsigned height)
		{
			glViewport(x, y, width, height);
		}

		void OpenGLRendererAPI::clearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void OpenGLRendererAPI::clearBuffers()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLRendererAPI::draw(std::shared_ptr<Graphics::VertexArray> vao, unsigned indexCount)
		{
			unsigned int count = indexCount ? indexCount : vao->getIndexBuffer()->getCount();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}

		void OpenGLRendererAPI::setDepthTest(bool enable)
		{
			if (enable)
			{
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
		}

		void OpenGLRendererAPI::setCullingMode(const Graphics::CullingMode& mode)
		{
			static Graphics::CullingMode currentMode = Graphics::CullingMode::Back;

			if (mode == currentMode)
			{
				return;
			}
			
			switch (mode)
			{
			case Graphics::CullingMode::None:			glDisable(GL_CULL_FACE); break;
			case Graphics::CullingMode::Front:			glEnable(GL_CULL_FACE); glCullFace(GL_FRONT); break;
			case Graphics::CullingMode::Back:			glEnable(GL_CULL_FACE); glCullFace(GL_BACK); break;
			case Graphics::CullingMode::FrontAndBack:	glEnable(GL_CULL_FACE); glCullFace(GL_FRONT_AND_BACK); break;
			}

			currentMode = mode;
		}
	}
}
#endif