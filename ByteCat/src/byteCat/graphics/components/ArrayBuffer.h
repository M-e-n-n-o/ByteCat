#pragma once

namespace BC
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		LOG_CRITICAL("Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		unsigned int size;
		unsigned int offset;
		bool normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}

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

			LOG_CRITICAL("Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_elements;
		unsigned int m_stride = 0;
		
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		unsigned int getStride() const { return m_stride; }
		const std::vector<BufferElement>& getElements() const { return m_elements; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	
	private:
		void CalculateOffsetsAndStride()
		{
			unsigned int offset = 0;
			m_stride = 0;
			
			for (auto& element : m_elements)
			{
				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
			}
		}
	};

	/// <summary>
	/// This class represents a vertex buffer which holds data about a model.
	/// Put this class inside a VertexArray to use it.
	/// </summary>
	class VertexBuffer
	{	
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setData(const void* data, unsigned int size) = 0;

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;

		static std::shared_ptr<VertexBuffer> Create(unsigned int size);
		static std::shared_ptr<VertexBuffer> Create(float* vertices, unsigned int size);
	};

	/// <summary>
	/// This specific vertex buffer holds data about the indices of a model.
	/// Put this class inside a VertexArray to use it.
	/// </summary>
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual unsigned int getCount() const = 0;

		static std::shared_ptr<IndexBuffer> Create(unsigned int* indices, unsigned int count);
	};
}
