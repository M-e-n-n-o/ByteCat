#pragma once

#include <vector>
#include <memory>
#include "byteCat/render/vertex-object/Buffer.h"

namespace BC
{
	class VertexArray
	{
	private:
		unsigned int id;
		unsigned int vboIndex = 0;
		
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;

		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);

		const unsigned int getId() const { return id; }
		const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers; }
		const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }

		static std::shared_ptr<VertexArray> Create()
		{
			return std::make_shared<VertexArray>();
		}
	};
}
