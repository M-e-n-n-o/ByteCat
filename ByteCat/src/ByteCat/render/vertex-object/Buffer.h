#pragma once

#include "byteCat/Log.h"

namespace BC
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
	
	struct BufferElement
	{
		ShaderDataType type;
		bool normalized;
	
		BufferElement() = default;
	
		BufferElement(ShaderDataType type, bool normalized = false): type(type), normalized(normalized) {}
	
		unsigned int getComponentCount() const
		{
			switch (type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3;
			case ShaderDataType::Mat4:    return 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}
	
			LOG_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	};
	
	class VertexBuffer
	{
	private:
		unsigned int id;
		BufferElement element = { ShaderDataType::None };

	public:
		VertexBuffer(unsigned int size);
		VertexBuffer(float* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		void setData(const void* data, unsigned int size);

		const BufferElement& getElement() const { return element; }
		void setBufferType(const BufferElement& newElement) { element = newElement; }
		
		static std::shared_ptr<VertexBuffer> Create(unsigned int size)
		{
			return std::make_shared<VertexBuffer>(size);
		}

		static std::shared_ptr<VertexBuffer> Create(float* data, unsigned int size)
		{
			return std::make_shared<VertexBuffer>(data, size);
		}
	};

	class IndexBuffer
	{
	private:
		unsigned int id;
		unsigned int count;
	
	public:
		IndexBuffer(unsigned int* indices, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		unsigned int getCount() const { return count; }

		
		static std::shared_ptr<IndexBuffer> Create(unsigned int* indices, unsigned int count)
		{
			return std::make_shared<IndexBuffer>(indices, count);
		}
	};
}
