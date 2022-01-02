#pragma once
#include "byteCat/graphics/objects/VertexArray.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLVertexArray : public VertexArray
		{
		private:
			unsigned int id;
			unsigned int vboIndex = 0;

			IndexBuffer* indexBuffer;
			std::vector<VertexBuffer*> vertexBuffers;
			
		public:
			OpenGLVertexArray();
			~OpenGLVertexArray();
			
			void bind() const override;
			void unbind() const override;
			
			void setIndexBuffer(IndexBuffer* buffer) override;
			void addVertexBuffer(VertexBuffer* buffer) override;

			const IndexBuffer* getIndexBuffer() const override { return indexBuffer; }
			const std::vector<VertexBuffer*>& getVertexBuffers() const override { return vertexBuffers; }
		};
	}
}
