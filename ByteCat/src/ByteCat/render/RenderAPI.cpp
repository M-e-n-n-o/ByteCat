#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/RenderAPI.h"

namespace BC
{
	namespace RenderAPI
	{
		static void OpenGLMessageCallback(
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
			case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_INFO(message); return;
			}

			LOG_ASSERT(false, "Unknown OpenGL message severity level");
		}
		
		void Init()
		{
		#ifdef BC_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
		}

		void SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
		{
			glViewport(x, y, width, height);
		}

		void ClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Draw(const std::shared_ptr<VertexArray>& vao, unsigned indexCount)
		{
			unsigned int count = indexCount ? indexCount : vao->getIndexBuffer()->getCount();
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}
}
