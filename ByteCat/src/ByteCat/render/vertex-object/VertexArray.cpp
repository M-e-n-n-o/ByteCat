#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/vertex-object/VertexArray.h"

namespace BC
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

		LOG_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}


	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(id);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		LOG_ASSERT((int) buffer->getElement().type, "Buffer does not have a buffer type");

		bind();
		buffer->bind();

		BufferElement element = buffer->getElement();
		
		switch (element.type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		{
			glEnableVertexAttribArray(vboIndex);
			glVertexAttribPointer(vboIndex, element.getComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE, 0, nullptr);
				
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
			glVertexAttribIPointer(vboIndex, element.getComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type), 0, nullptr);
				
			vboIndex++;
			break;
		}
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
		{
			uint8_t count = element.getComponentCount();
			for (uint8_t i = 0; i < count; i++)
			{
				glEnableVertexAttribArray(vboIndex);
				glVertexAttribPointer(vboIndex, count, ShaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE, 0, nullptr);
				
				glVertexAttribDivisor(vboIndex, 1);
				vboIndex++;
			}
			break;
		}
		default:
			LOG_ASSERT(false, "Unknown ShaderDataType");
		}

		vertexBuffers.push_back(buffer);
	}

	void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		glBindVertexArray(id);
		buffer->bind();

		indexBuffer = buffer;
	}
}
