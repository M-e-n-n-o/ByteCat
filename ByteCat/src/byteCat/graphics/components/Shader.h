#pragma once
#include <glm/glm.hpp>
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Graphics
	{
		/**
		 * @brief
		 * This class represents a shader program which is needed to render with a VertexArray.
		 */
		class Shader
		{
		public:
			virtual ~Shader() = default;

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual void loadInt(const std::string& name, int value) = 0;
			virtual void loadIntArray(const std::string& name, int* values, unsigned int count) = 0;
			virtual void loadFloat(const std::string& name, float value) = 0;
			virtual void loadVector2(const std::string& name, const glm::vec2& value) = 0;
			virtual void loadVector3(const std::string& name, const glm::vec3& value) = 0;
			virtual void loadVector3Array(const std::string& name, const std::vector<glm::vec3>& values) = 0;
			virtual void loadVector4(const std::string& name, const glm::vec4& value) = 0;
			virtual void loadMatrix4(const std::string& name, const glm::mat4& value) = 0;

			virtual void linkUniformBuffer(const std::string& bufferName, unsigned int bindingIndex) = 0;

			virtual void addTexture(const char* textureName, std::shared_ptr<Texture> texture) = 0;
			virtual void activateTextures() = 0;

			virtual const std::string& getName() const = 0;

			static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, bool isFilePath);
			static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc, bool isFilePath);
		};

		class ComputeShader
		{
		public:
			virtual ~ComputeShader() = default;

			virtual void compute(unsigned numberOfGroupsX, unsigned numberOfGroupsY, unsigned numberOfGroupsZ) = 0;
			virtual void waitToFinish() = 0;

			virtual void setOutputTexture(std::shared_ptr<Texture> texture, unsigned int textureUnit = 0) = 0;

			virtual const std::string& getName() const = 0;

			static std::shared_ptr<ComputeShader> Create(const std::string& name, const std::string& computeSrc, bool isFilePath = true);
		};
	}
}
