#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLUniformBuffer.h"

namespace BC
{
	namespace Platform
	{		
		OpenGLUniformBuffer::OpenGLUniformBuffer(const std::string& blockName, unsigned bindingIndex, unsigned size): m_blockName(blockName), m_bindingIndex(bindingIndex)
		{
			glGenBuffers(1, &m_id);
			glBindBuffer(GL_UNIFORM_BUFFER, m_id);

			glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			
 			glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, m_id);
		}

		OpenGLUniformBuffer::OpenGLUniformBuffer(const std::string& blockName, unsigned bindingIndex, unsigned size,
			const void* data): m_blockName(blockName), m_bindingIndex(bindingIndex)
		{			
			glGenBuffers(1, &m_id);
			glBindBuffer(GL_UNIFORM_BUFFER, m_id);
			
			glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, m_id);
			
			glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
		}

		OpenGLUniformBuffer::~OpenGLUniformBuffer()
		{
			glDeleteBuffers(1, &m_id);
		}

		void OpenGLUniformBuffer::bind() const
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		}

		void OpenGLUniformBuffer::unbind() const
		{
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		void OpenGLUniformBuffer::loadData(const void* data, unsigned size, unsigned offset)
		{
			bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		}
	}
}
#endif