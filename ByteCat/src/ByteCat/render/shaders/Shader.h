#pragma once

#include <map>
#include <unordered_map>
#include <glm/gtc/matrix_transform.hpp>
#include "byteCat/render/textures/Texture.h"

namespace BC
{
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

		std::map<unsigned int, std::shared_ptr<Texture>> textures;

		mutable std::unordered_map<std::string, int> uniformLocationCache;
	
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
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

		bool operator<(const Shader& other) const
		{
			return programID < other.programID;
		}
		
		// Use this function to create a custom shader
		static std::shared_ptr<Shader> Create(std::string& vertexShader, std::string& fragmentShader)
		{
			return std::make_shared<Shader>(vertexShader, fragmentShader);
		}
	
	private:
		int getUniformLocation(std::string& uniformName) const;

		int loadShader(const std::string& shader, int type) const;
	};
}


namespace std
{
	template<>
	struct less<shared_ptr<BC::Shader>>
	{
		volatile bool operator() (const shared_ptr<BC::Shader>& lhs, const shared_ptr<BC::Shader>& rhs) const
		{
			return *lhs < *rhs;
		}
	};
}