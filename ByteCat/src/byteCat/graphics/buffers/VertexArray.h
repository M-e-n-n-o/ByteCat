#pragma once
#include <vector>
#include "byteCat/graphics/buffers/ArrayBuffer.h"

namespace BC
{
	/// <summary>
	/// This class, when filled with an index buffer and vertex buffer(s),
	/// can be rendered together with a shader.
	/// </summary>
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setIndexBuffer(std::shared_ptr<IndexBuffer> buffer) = 0;
		virtual void addVertexBuffer(std::shared_ptr<VertexBuffer> buffer) = 0;

		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;

		static std::shared_ptr<VertexArray> Create();
	};
}
