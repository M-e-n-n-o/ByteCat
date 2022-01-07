#pragma once
#include "byteCat/graphics/buffers/UniformBuffer.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLUniformBuffer : public UniformBuffer
		{
		private:
			unsigned int id;
			
			std::string blockName;
			unsigned int bindingIndex;
		
		public:
			OpenGLUniformBuffer(const std::string& blockName, unsigned int bindingIndex, unsigned int size);
			OpenGLUniformBuffer(const std::string& blockName, unsigned int bindingIndex, unsigned int size, const void* data);
			~OpenGLUniformBuffer();
			
			void bind() const override;
			void unbind() const override;

			void loadData(const void* data, unsigned int size, unsigned int offset) override;
			
			const std::string& getName() const override { return blockName; }
			unsigned getBindingIndex() const override { return bindingIndex; }
		};
	}
}
