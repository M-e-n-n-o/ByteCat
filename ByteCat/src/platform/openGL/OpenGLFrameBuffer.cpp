#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLFrameBuffer.h"

#include "byteCat/app/Application.h"

namespace BC
{
	namespace Platform
	{
		OpenGLFrameBuffer::OpenGLFrameBuffer(const std::string& name, unsigned width, unsigned height): m_name(name), m_width(width), m_height(height)
		{			
			glGenFramebuffers(1, &m_id);
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		}

		OpenGLFrameBuffer::~OpenGLFrameBuffer()
		{
			glDeleteFramebuffers(1, &m_id);
		}

		void OpenGLFrameBuffer::bind() const
		{
			if (!isComplete())
			{
				LOG_WARN("Framebuffer {0} is not yet complete", m_name);
			}
			
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
			glViewport(0, 0, m_width, m_height);
		}

		void OpenGLFrameBuffer::unbind() const
		{
			auto& window = Application::GetInstance().getWindow();
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glViewport(0, 0, window.getWidth(), window.getHeight());
		}

		bool OpenGLFrameBuffer::isComplete() const
		{
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			{
				return true;
			}

			return false;
		}

		void OpenGLFrameBuffer::attachTexture(std::shared_ptr<Texture2D> texture, unsigned int slot)
		{
			switch (texture->getFormat())
			{
			case TextureFormat::DEPTH:			
				glBindTexture(GL_TEXTURE_2D, texture->getId());
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->getId(), 0);
				return;
				
			case TextureFormat::DEPTH_STENCIL:	
				glBindTexture(GL_TEXTURE_2D, texture->getId());
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture->getId(), 0);
				return;
				
			case TextureFormat::R:
			case TextureFormat::RG:
			case TextureFormat::RGB16F:
			case TextureFormat::RGBA16F:
				glBindTexture(GL_TEXTURE_2D, texture->getId());
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, texture->getId(), 0);
				return;
			}

			LOG_WARN("Could not attach the texture to the frame buffer");
		}

		void OpenGLFrameBuffer::attachRenderBuffer(const TextureFormat& format)
		{
			glGenRenderbuffers(1, &m_renderBufferId);
			glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);

			switch (format)
			{
			case TextureFormat::DEPTH:			
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);
				return;
				
			case TextureFormat::DEPTH_STENCIL:	
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, m_width, m_height);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);
				return;
				
			default:							
				LOG_WARN("Unvalid texture format for render buffer");
				glDeleteRenderbuffers(1, &m_renderBufferId);
				return;
			}
		}
	}
}
