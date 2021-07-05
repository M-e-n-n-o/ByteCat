#pragma once

#include <map>
#include <unordered_map>
#include <glm/gtc/matrix_transform.hpp>
#include "byteCat/render/models/Texture.h"
#include "byteCat/render/shaders/ByteCatShaders.h"

namespace BC
{
	// This enum holds all the names of each predefined ByteCat shader
	enum class ByteCatShader
	{
		Standard
	};

	/*
	 * Class Shader:
	 *		This class represents a ByteCat shader which is used to render a VertexArray with.
	 */
	class Shader
	{
	private:
		int programID;
		int vertexShaderID;
		int fragmentShaderID;

		bool hasTextures;
		std::map<unsigned int, std::shared_ptr<Texture>> textures;

		mutable std::unordered_map<std::string, int> uniformLocationCache;
	
	public:
		Shader(std::string& vertexShader, std::string& fragmentShader);
		virtual ~Shader();

		// Call this function to bind the shader
		void bind() const;
		// Call this funtion to unbind the shader
		void unbind() const;

		// Call the functions below to load a value into a uniform shader variable
		void loadFloat(std::string name, float value) const;
		void loadInt(std::string name, int value) const;
		void loadVector2(std::string name, glm::vec2 value) const;
		void loadVector3(std::string name, glm::vec3 value) const;
		void loadVector4(std::string name, glm::vec4 value) const;
		void loadMatrix4(std::string name, glm::mat4 value) const;

		// Use this function to add a Texture to the shader on the given location (textureUnit)
		void setTexture(std::shared_ptr<Texture> texture, unsigned int textureUnit = 0);
		// This function gets called when a VAO, which uses this shader, gets rendered
		void bindTextures() const;

		// Use this function to create a custom shader
		static std::shared_ptr<Shader> Create(std::string& vertexShader, std::string& fragmentShader)
		{
			return std::make_shared<Shader>(vertexShader, fragmentShader);
		}

		// Use this function to create a predefined ByteCat shader
		static std::shared_ptr<Shader> Create(ByteCatShader const& shaderType)
		{
			switch (shaderType)
			{
			case ByteCatShader::Standard : return Create(shaders::standard::vertexShader, shaders::standard::fragmentShader);
			}

			LOG_ERROR("ByteCat shadertype \"{0}\" not found", shaderType);
			return Create(std::string("ERROR"), std::string("ERROR"));
		}
	
	private:
		int getUniformLocation(std::string& uniformName) const;

		int loadShader(std::string& shader, int type) const;
	};
}
