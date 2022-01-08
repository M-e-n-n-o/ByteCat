#pragma once
#include "byteCat/graphics/buffers/Shader.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLShader : public Shader
		{

			
		private:
			std::string name;
			unsigned int programID;

			mutable std::unordered_map<std::string, unsigned int> uniformLocationCache;
			
		public:
			OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
			~OpenGLShader();
			
			void bind() const override;
			void unbind() const override;
			
			void loadInt(const std::string& name, int value) override;
			void loadIntArray(const std::string& name, int* values, unsigned count) override;
			void loadFloat(const std::string& name, float value) override;
			void loadVector2(const std::string& name, const glm::vec2& value) override;
			void loadVector3(const std::string& name, const glm::vec3& value) override;
			void loadVector4(const std::string& name, const glm::vec4& value) override;
			void loadMatrix4(const std::string& name, const glm::mat4& value) override;

			void linkUniformBuffer(const std::string& bufferName, unsigned int bindingIndex) override;
			
			const std::string& getName() const override { return name; }

		private:
			int getUniformLocation(const std::string& uniformName) const;
			
			unsigned int loadShader(const std::string& shader, int type) const;
		};
	}
}
