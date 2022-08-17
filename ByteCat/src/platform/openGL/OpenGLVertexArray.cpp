#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
#include "bcpch.h"

#include <glad/glad.h>
#include "platform/openGL/OpenGLVertexArray.h"

namespace BC
{
	namespace Platform
	{
		static GLenum ShaderDataTypeToOpenGLBaseType(Graphics::ShaderDataType type)
		{
			switch (type)
			{
			case Graphics::ShaderDataType::Float:    return GL_FLOAT;
			case Graphics::ShaderDataType::Float2:   return GL_FLOAT;
			case Graphics::ShaderDataType::Float3:   return GL_FLOAT;
			case Graphics::ShaderDataType::Float4:   return GL_FLOAT;
			case Graphics::ShaderDataType::Mat3:     return GL_FLOAT;
			case Graphics::ShaderDataType::Mat4:     return GL_FLOAT;
			case Graphics::ShaderDataType::Int:      return GL_INT;
			case Graphics::ShaderDataType::Int2:     return GL_INT;
			case Graphics::ShaderDataType::Int3:     return GL_INT;
			case Graphics::ShaderDataType::Int4:     return GL_INT;
			case Graphics::ShaderDataType::Bool:     return GL_BOOL;
			}

			LOG_CRITICAL("Unknown ShaderDataType!");
			return 0;
		}
		
		OpenGLVertexArray::OpenGLVertexArray()
		{
			glGenVertexArrays(1, &m_id);
		}

		OpenGLVertexArray::~OpenGLVertexArray()
		{	
			glDeleteVertexArrays(1, &m_id);
		}

		void OpenGLVertexArray::bind() const
		{
			glBindVertexArray(m_id);
		}

		void OpenGLVertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

		void OpenGLVertexArray::setIndexBuffer(std::shared_ptr<Graphics::IndexBuffer> buffer)
		{
			glBindVertexArray(m_id);
			buffer->bind();

			indexBuffer = buffer;
		}

		void OpenGLVertexArray::addVertexBuffer(std::shared_ptr<Graphics::VertexBuffer> buffer)
		{
			if (buffer->getLayout().getElements().empty())
			{
				LOG_CRITICAL("VertexBuffer has no layout!");
			}

			glBindVertexArray(m_id);
			buffer->bind();

			const auto& layout = buffer->getLayout();				
			for (const auto& element : layout)
			{
				switch (element.type)
				{
				case Graphics::ShaderDataType::Float:
				case Graphics::ShaderDataType::Float2:
				case Graphics::ShaderDataType::Float3:
				case Graphics::ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(m_vboIndex);
					glVertexAttribPointer(m_vboIndex, element.getComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)element.offset);
					m_vboIndex++;
					break;
				}
				case Graphics::ShaderDataType::Int:
				case Graphics::ShaderDataType::Int2:
				case Graphics::ShaderDataType::Int3:
				case Graphics::ShaderDataType::Int4:
				case Graphics::ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(m_vboIndex);
					glVertexAttribIPointer(m_vboIndex, element.getComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type),
						layout.getStride(), (const void*)element.offset);
					m_vboIndex++;
					break;
				}
				case Graphics::ShaderDataType::Mat3:
				case Graphics::ShaderDataType::Mat4:
				{
					unsigned int count = element.getComponentCount();
					for (unsigned int i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_vboIndex);
						glVertexAttribPointer(m_vboIndex, count, ShaderDataTypeToOpenGLBaseType(element.type),
							element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)(element.offset + sizeof(float) * count * i));
						glVertexAttribDivisor(m_vboIndex, 1);
						m_vboIndex++;
					}
					break;
				}
				default:
					LOG_ERROR("Unknown ShaderDataType!");
				}
			}

			vertexBuffers.push_back(buffer);
		}
	}
}

#endif