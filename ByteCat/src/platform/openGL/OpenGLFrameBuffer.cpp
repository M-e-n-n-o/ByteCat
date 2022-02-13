#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLFrameBuffer.h"

#include "byteCat/app/Application.h"

namespace BC
{
	namespace Platform
	{
		OpenGLFrameBuffer::OpenGLFrameBuffer()
		{
			glGenFramebuffers(1, &m_id);
		}

		OpenGLFrameBuffer::~OpenGLFrameBuffer()
		{
		}

		void OpenGLFrameBuffer::bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
			//glViewport(0, 0, frameBufferWidth, frameBufferHeight);
		}

		void OpenGLFrameBuffer::unbind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			auto& window = Application::GetInstance().getWindow();
			glViewport(0, 0, window.getWidth(), window.getHeight());
		}
	}
}
