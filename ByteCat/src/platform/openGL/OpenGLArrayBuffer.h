#pragma once
#include "byteCat/graphics/components/ArrayBuffer.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLVertexBuffer : public VertexBuffer
		{
		private:
			unsigned int m_id;
			BufferLayout m_layout;

		public:
			OpenGLVertexBuffer(unsigned int size);
			OpenGLVertexBuffer(float* vertices, unsigned int size);
			~OpenGLVertexBuffer();

			void bind() const override;
			void unbind() const override;
			
			void setData(const void* data, unsigned size) override;
			
			const BufferLayout& getLayout() const override { return m_layout; }
			void setLayout(const BufferLayout& layout) override { this->m_layout = layout; }
		};
		
		class OpenGLIndexBuffer : public IndexBuffer
		{
		private:
			unsigned int m_id;
			unsigned int m_count;

		public:
			OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
			~OpenGLIndexBuffer();

			void bind() const override;
			void unbind() const override;
			
			unsigned getCount() const override { return m_count; }
		};
	}
}
