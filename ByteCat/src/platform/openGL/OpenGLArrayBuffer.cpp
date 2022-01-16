#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLArrayBuffer.h"

namespace BC
{
	namespace Platform
	{
		// --------------------------------------------------------------------
		// ------------------------ Vertex Buffer -----------------------------
		// --------------------------------------------------------------------
		
		OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned size)
		{
			glGenBuffers(1, &m_id);
			
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		}

		OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned size)
		{
			glGenBuffers(1, &m_id);
			
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}

		OpenGLVertexBuffer::~OpenGLVertexBuffer()
		{
			glDeleteBuffers(1, &m_id);
		}

		void OpenGLVertexBuffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}

		void OpenGLVertexBuffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void OpenGLVertexBuffer::setData(const void* data, unsigned size)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		}
		
		// --------------------------------------------------------------------
		// ------------------------- Index Buffer -----------------------------
		// --------------------------------------------------------------------

		OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned* indices, unsigned count) : m_count(count)
		{
			glGenBuffers(1, &m_id);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
		}

		OpenGLIndexBuffer::~OpenGLIndexBuffer()
		{
			glDeleteBuffers(1, &m_id);
		}

		void OpenGLIndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}

		void OpenGLIndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
