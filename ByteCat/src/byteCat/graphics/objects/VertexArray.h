#pragma once
#include <vector>
#include "byteCat/graphics/objects/Buffer.h"

namespace BC
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setIndexBuffer(IndexBuffer* buffer) = 0;
		virtual void addVertexBuffer(VertexBuffer* buffer) = 0;

		virtual const IndexBuffer* getIndexBuffer() const = 0;
		virtual const std::vector<VertexBuffer*>& getVertexBuffers() const = 0;

		static VertexArray* Create();
	};
}
