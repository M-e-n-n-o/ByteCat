#pragma once
#include "byteCat/graphics/buffers/VertexArray.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLVertexArray : public VertexArray
		{
		private:
			unsigned int m_id;
			unsigned int m_vboIndex = 0;

			std::shared_ptr<IndexBuffer> indexBuffer;
			std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
			
		public:
			OpenGLVertexArray();
			~OpenGLVertexArray();
			
			void bind() const override;
			void unbind() const override;
			
			void setIndexBuffer(std::shared_ptr<IndexBuffer> buffer) override;
			void addVertexBuffer(std::shared_ptr<VertexBuffer> buffer) override;

			const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return indexBuffer; }
			const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return vertexBuffers; }
		};
	}
}
