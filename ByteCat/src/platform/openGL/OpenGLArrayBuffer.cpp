#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLArrayBuffer.h"

#include "platform/CommandExecutor.h"

namespace BC
{
	namespace Platform
	{
		// --------------------------------------------------------------------
		// ------------------------ Vertex Buffer -----------------------------
		// --------------------------------------------------------------------
		
		OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned size)
		{			
			CommandExecutor::PushCommand([this, size]()
			{
				glGenBuffers(1, &m_id);

				glBindBuffer(GL_ARRAY_BUFFER, m_id);
				glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			});
		}

		OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned size)
		{
			CommandExecutor::PushCommand([this, vertices, size]()
			{
				glGenBuffers(1, &m_id);

				glBindBuffer(GL_ARRAY_BUFFER, m_id);
				glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
			});
		}

		OpenGLVertexBuffer::~OpenGLVertexBuffer()
		{
			CommandExecutor::PushCommand([id = m_id]()
			{
				glDeleteBuffers(1, &id);
			});
		}

		void OpenGLVertexBuffer::bind() const
		{
			CommandExecutor::PushCommand([this]()
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_id);
			});
		}

		void OpenGLVertexBuffer::unbind() const
		{
			CommandExecutor::PushCommand([]()
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			});
		}

		void OpenGLVertexBuffer::setData(const void* data, unsigned size)
		{
			CommandExecutor::PushCommand([this, data, size]()
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_id);
				glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
			});
		}
		
		// --------------------------------------------------------------------
		// ------------------------- Index Buffer -----------------------------
		// --------------------------------------------------------------------

		OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned* indices, unsigned count) : m_count(count)
		{
			CommandExecutor::PushCommand([this, indices, count]()
			{
				glGenBuffers(1, &m_id);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
			});
		}

		OpenGLIndexBuffer::~OpenGLIndexBuffer()
		{
			CommandExecutor::PushCommand([id = m_id]()
			{
				glDeleteBuffers(1, &id);
			});
		}

		void OpenGLIndexBuffer::bind() const
		{
			CommandExecutor::PushCommand([this]()
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
			});
		}

		void OpenGLIndexBuffer::unbind() const
		{
			CommandExecutor::PushCommand([]()
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			});
		}
	}
}
