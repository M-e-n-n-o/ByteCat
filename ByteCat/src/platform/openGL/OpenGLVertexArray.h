#pragma once
#ifdef BC_PLATFORM_PC

#include "byteCat/graphics/components/VertexArray.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLVertexArray : public Graphics::VertexArray
		{
		private:
			unsigned int m_id;
			unsigned int m_vboIndex = 0;

			std::shared_ptr<Graphics::IndexBuffer> indexBuffer;
			std::vector<std::shared_ptr<Graphics::VertexBuffer>> vertexBuffers;
			
		public:
			OpenGLVertexArray();
			~OpenGLVertexArray();

			void bind() const override;
			void unbind() const override;
			
			void setIndexBuffer(std::shared_ptr<Graphics::IndexBuffer> buffer) override;
			void addVertexBuffer(std::shared_ptr<Graphics::VertexBuffer> buffer) override;

			const std::shared_ptr<Graphics::IndexBuffer>& getIndexBuffer() const override { return indexBuffer; }
			const std::vector<std::shared_ptr<Graphics::VertexBuffer>>& getVertexBuffers() const override { return vertexBuffers; }
		};
	}
}
#endif