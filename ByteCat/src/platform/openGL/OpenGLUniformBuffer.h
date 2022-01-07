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

			BufferLayout layout;
		
		public:
			OpenGLUniformBuffer(const std::string& blockName, unsigned int bindingIndex);
			~OpenGLUniformBuffer();
			
			void bind() const override;
			void unbind() const override;
			
			void setLayout(const BufferLayout& layout) override;
			
			void loadInt(const std::string& name, int value) override;
			void loadFloat(const std::string& name, float value) override;
			void loadVector2(const std::string& name, const glm::vec2& value) override;
			void loadVector3(const std::string& name, const glm::vec3& value) override;
			void loadVector4(const std::string& name, const glm::vec4& value) override;
			void loadMatrix4(const std::string& name, const glm::mat4& value) override;

			const std::string& getName() const override { return blockName; }
			unsigned getBindingIndex() const override { return bindingIndex; }

		private:
			bool getSizeAndOffset(const std::string& name, const ShaderDataType& type, unsigned& size, unsigned& offset);
		};
	}
}
