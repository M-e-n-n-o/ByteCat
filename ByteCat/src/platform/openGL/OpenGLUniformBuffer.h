#pragma once
#include "byteCat/graphics/components/UniformBuffer.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLUniformBuffer : public Graphics::UniformBuffer
		{
		private:
			unsigned int m_id;
			
			std::string m_blockName;
			unsigned int m_bindingIndex;
		
		public:
			OpenGLUniformBuffer(const std::string& blockName, unsigned int bindingIndex, unsigned int size);
			OpenGLUniformBuffer(const std::string& blockName, unsigned int bindingIndex, unsigned int size, const void* data);
			~OpenGLUniformBuffer();
			
			void bind() const override;
			void unbind() const override;

			void loadData(const void* data, unsigned int size, unsigned int offset) override;
			
			const std::string& getName() const override { return m_blockName; }
			unsigned getBindingIndex() const override { return m_bindingIndex; }
		};
	}
}
