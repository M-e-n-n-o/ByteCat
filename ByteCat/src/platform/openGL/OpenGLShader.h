#pragma once
#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
#include "byteCat/graphics/components/Shader.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLShader : public Graphics::Shader
		{
		private:
			std::string m_name;
			unsigned int m_programID;

			//int m_textureSlot = -1;
			std::vector<std::shared_ptr<Graphics::Texture>> m_textures;

			mutable std::unordered_map<std::string, unsigned int> m_uniformLocationCache;
			
		public:
			OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, bool isFilePath);
			OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc, bool isFilePath);
			~OpenGLShader();
			
			void bind() const override;
			void unbind() const override;
			
			void loadInt(const std::string& name, int value) override;
			void loadIntArray(const std::string& name, int* values, unsigned count) override;
			void loadFloat(const std::string& name, float value) override;
			void loadVector2(const std::string& name, const glm::vec2& value) override;
			void loadVector3(const std::string& name, const glm::vec3& value) override;
			void loadVector3Array(const std::string& name, const std::vector<glm::vec3>& values) override;
			void loadVector4(const std::string& name, const glm::vec4& value) override;
			void loadMatrix4(const std::string& name, const glm::mat4& value) override;

			void linkUniformBuffer(const std::string& bufferName, unsigned int bindingIndex) override;

			void addTexture(const char* textureName, std::shared_ptr<Graphics::Texture> texture) override;
			void activateTextures() override;
			
			const std::string& getName() const override { return m_name; }

		private:
			int getUniformLocation(const std::string& uniformName) const;
			
			unsigned int loadShader(const std::string& shader, int type) const;
		};
	}
}
#endif