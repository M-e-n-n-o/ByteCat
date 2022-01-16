#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLRendererAPI.h"

#include "platform/PlatformAPI.h"

namespace BC
{
	namespace Platform
	{
		void OpenGLMessageCallback(
			unsigned source,
			unsigned type,
			unsigned id,
			unsigned severity,
			int length,
			const char* message,
			const void* userParam)
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:         LOG_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       LOG_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          LOG_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_WARN(message); return;
			}

			LOG_CRITICAL("Unknown OpenGL message severity level!");
		}
		
		OpenGLRendererAPI::OpenGLRendererAPI()
		{
			#ifdef BC_ENABLE_LOG
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(OpenGLMessageCallback, nullptr);

				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
			#endif

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
		}

		void OpenGLRendererAPI::setViewport(unsigned x, unsigned y, unsigned width, unsigned height)
		{
			glViewport(x, y, width, height);
		}

		void OpenGLRendererAPI::clearColor(const glm::vec4& color)
		{
			API::PushCommand([color]()
			{
				glClearColor(color.r, color.g, color.b, color.a);
			});
		}

		void OpenGLRendererAPI::clearBuffers()
		{
			API::PushCommand([]()
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			});
			
		}

		void OpenGLRendererAPI::draw(std::shared_ptr<VertexArray> vao, unsigned indexCount)
		{
			unsigned int count = indexCount ? indexCount : vao->getIndexBuffer()->getCount();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
	}
}
