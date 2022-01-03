#pragma once
#include "byteCat/graphics/vertexObjects/Buffer.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLVertexBuffer : public VertexBuffer
		{
		private:
			unsigned int id;
			BufferLayout layout;

		public:
			OpenGLVertexBuffer(unsigned int size);
			OpenGLVertexBuffer(float* vertices, unsigned int size);
			~OpenGLVertexBuffer();

			void bind() const override;
			void unbind() const override;
			
			void setData(const void* data, unsigned size) override;
			
			const BufferLayout& getLayout() const override { return layout; }
			void setLayout(const BufferLayout& layout) override { this->layout = layout; }
		};
		
		class OpenGLIndexBuffer : public IndexBuffer
		{
		private:
			unsigned int id;
			unsigned int count;

		public:
			OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
			~OpenGLIndexBuffer();

			void bind() const override;
			void unbind() const override;
			
			unsigned getCount() const override { return count; }
		};
	}
}
