#include "bcpch.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "byteCat/render/shaders/Shader.h"

namespace BC
{	
	Shader::Shader(std::string& vertexShader, std::string& fragmentShader)
	{
		hasTextures = (fragmentShader.find("sampler") != std::string::npos);
		
		vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
		fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);

		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		
		glLinkProgram(programID);
		glValidateProgram(programID);
	}

	Shader::~Shader()
	{
		glUseProgram(0);
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
	}

	void Shader::bind() const
	{
		glUseProgram(programID);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	void Shader::loadFloat(std::string name, float value) const
	{
		GLint location = getUniformLocation(name);
		if (location != -1)
		{
			glUniform1f(location, value);
		}
	}

	void Shader::loadInt(std::string name, int value) const
	{
		GLint location = getUniformLocation(name);
		if (location != -1)
		{
			glUniform1i(location, value);
		}
	}

	void Shader::loadVector2(std::string name, glm::vec2 value) const
	{
		GLint location = getUniformLocation(name);
		if (location != -1)
		{
			glUniform2fv(location, 1, glm::value_ptr(value));
		}
	}

	void Shader::loadVector3(std::string name, glm::vec3 value) const
	{
		GLint location = getUniformLocation(name);
		if (location != -1)
		{
			glUniform3fv(location, 1, glm::value_ptr(value));
		}
	}

	void Shader::loadVector4(std::string name, glm::vec4 value) const
	{
		GLint location = getUniformLocation(name);
		if (location != -1)
		{
			glUniform4fv(location, 1, glm::value_ptr(value));
		}
	}

	void Shader::loadMatrix4(std::string name, glm::mat4 value) const
	{
		GLint location = getUniformLocation(name);
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
	}

	void Shader::setTexture(std::shared_ptr<Texture> texture, unsigned textureUnit)
	{
		auto it = textures.insert(std::pair<unsigned int, std::shared_ptr<Texture>>(textureUnit, texture));
		
		if (!it.second)
		{
			it.first->second = texture;
		}
	}

	void Shader::bindTextures() const
	{
		for (auto texture : textures)
		{
			texture.second->bind(texture.first);
		}
	}

	int Shader::getUniformLocation(std::string& uniformName) const
	{
		if (uniformLocationCache.find(uniformName) != uniformLocationCache.end())
		{
			return uniformLocationCache[uniformName];
		}
		
		GLint location = glGetUniformLocation(programID, uniformName.c_str());
		if (location == -1)
		{
			LOG_ERROR("Variable \"{0}\" not found in the shader code", uniformName);
			return -1;
		}

		uniformLocationCache[uniformName] = location;
		
		return location;
	}

	int Shader::loadShader(std::string& shader, int type) const
	{
		const GLchar* shaderText = shader.c_str();
		const GLuint shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderText, NULL);
		glCompileShader(shaderID);

		GLint succes = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
		if (succes == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
			for (std::vector<GLchar>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
			{
				std::cout << *i;
			}
			std::cout << std::endl;
			LOG_ASSERT(false, "Could not compile shader");
			std::exit(-1);
		}

		return shaderID;
	}
}