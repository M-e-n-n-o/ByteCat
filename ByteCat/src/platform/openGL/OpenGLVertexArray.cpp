#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLVertexArray.h"

namespace BC
{
	namespace Platform
	{
		static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
			}

			LOG_CRITICAL("Unknown ShaderDataType!");
			return 0;
		}
		
		OpenGLVertexArray::OpenGLVertexArray()
		{
			glGenVertexArrays(1, &id);
		}

		OpenGLVertexArray::~OpenGLVertexArray()
		{	
			glDeleteVertexArrays(1, &id);
		}

		void OpenGLVertexArray::bind() const
		{
			glBindVertexArray(id);
		}

		void OpenGLVertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

		void OpenGLVertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
		{
			bind();
			buffer->bind();

			indexBuffer = buffer;
		}

		void OpenGLVertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
		{
			if (buffer->getLayout().getElements().empty())
			{
				LOG_CRITICAL("VertexBuffer has no layout!");
			}

			bind();
			buffer->bind();

			const auto& layout = buffer->getLayout();
			for (const auto& element : layout)
			{
				switch (element.type)
				{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(vboIndex);
					glVertexAttribPointer(vboIndex, element.getComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type), 
						element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)element.offset);
					vboIndex++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(vboIndex);
					glVertexAttribIPointer(vboIndex, element.getComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type),
						layout.getStride(), (const void*)element.offset);
					vboIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					unsigned int count = element.getComponentCount();
					for (unsigned int i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(vboIndex);
						glVertexAttribPointer(vboIndex, count, ShaderDataTypeToOpenGLBaseType(element.type),
							element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)(element.offset + sizeof(float) * count * i));
						glVertexAttribDivisor(vboIndex, 1);
						vboIndex++;
					}
					break;
				}
				default:
					LOG_CRITICAL("Unknown ShaderDataType!");
				}
			}

			vertexBuffers.push_back(buffer);
		}
	}
}
