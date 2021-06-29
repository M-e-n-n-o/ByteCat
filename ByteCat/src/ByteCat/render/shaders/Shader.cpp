#include "bcpch.h"
#include <glm/gtc/type_ptr.hpp>
#include "byteCat/render/shaders/Shader.h"

namespace BC
{	
	Shader::Shader(std::string& vertexShader, std::string& fragmentShader, std::function<void()> setTextures)
	{
		setTexturesFunc = setTextures;
		
		vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
		fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);

		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		
		bindAttributes();
		glLinkProgram(programID);
		glValidateProgram(programID);
		// getAllUniformLocations();
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

	// void Shader::loadUniformVariable(std::string variableName, ShaderUniformVariableValue value)
	// {
	// 	for (auto& variable : uniformVariables)
	// 	{
	// 		if (variable.name == variableName)
	// 		{
	// 			switch (variable.type)
	// 			{
	// 			case ShaderUniformVariableType::Float: glUniform1f(variable.location, value.Float); break;
	// 			case ShaderUniformVariableType::Int: glUniform1i(variable.location, value.Int); break;
	// 			case ShaderUniformVariableType::Vector2: glUniform2fv(variable.location, 1, glm::value_ptr(value.Vector2)); break;
	// 			case ShaderUniformVariableType::Vector3: glUniform3fv(variable.location, 1, glm::value_ptr(value.Vector3)); break;
	// 			case ShaderUniformVariableType::Vector4: glUniform4fv(variable.location, 1, glm::value_ptr(value.Vector4)); break;
	// 			case ShaderUniformVariableType::Matrix4: glUniformMatrix4fv(variable.location, 1, GL_FALSE, glm::value_ptr(value.Matrix4)); break;
	// 			default: LOG_ERROR("The value is not a valid type");
	// 			}
	//
	// 			return;
	// 		}
	// 	}
	//
	// 	LOG_ERROR("Variable \"{0}\" not found in the shader code", variableName);
	// }

	void Shader::loadFloat(std::string name, float value) const
	{
		GLint location = getUniformLocation(name.c_str());
		if (location != -1)
		{
			glUniform1f(location, value);
		}
	}

	void Shader::loadInt(std::string name, int value) const
	{
		GLint location = getUniformLocation(name.c_str());
		if (location != -1)
		{
			glUniform1i(location, value);
		}
	}

	void Shader::loadVector2(std::string name, glm::vec2 value) const
	{
		GLint location = getUniformLocation(name.c_str());
		if (location != -1)
		{
			glUniform2fv(location, 1, glm::value_ptr(value));
		}
	}

	void Shader::loadVector3(std::string name, glm::vec3 value) const
	{
		GLint location = getUniformLocation(name.c_str());
		if (location != -1)
		{
			glUniform3fv(location, 1, glm::value_ptr(value));
		}
	}

	void Shader::loadVector4(std::string name, glm::vec4 value) const
	{
		GLint location = getUniformLocation(name.c_str());
		if (location != -1)
		{
			glUniform4fv(location, 1, glm::value_ptr(value));
		}
	}

	void Shader::loadMatrix4(std::string name, glm::mat4 value) const
	{
		GLint location = getUniformLocation(name.c_str());
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
	}

	// void Shader::getAllUniformLocations()
	// {
	// 	int totalVariables;
	// 	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &totalVariables);
	//
	// 	for (unsigned int i = 0; i < totalVariables; i++)
	// 	{
	// 		int length;
	// 		int size;
	// 		GLenum type;
	// 		char name[64];
	// 		glGetActiveUniform(programID, i, sizeof(name), &length, &size, &type, name);
	//
	// 		ShaderUniformVariableType variableType;
	// 		switch (type)
	// 		{
	// 		case GL_FLOAT: variableType = ShaderUniformVariableType::Float; break;
	// 		case GL_INT: variableType = ShaderUniformVariableType::Int; break;
	// 		case GL_FLOAT_VEC2: variableType = ShaderUniformVariableType::Vector2; break;
	// 		case GL_FLOAT_VEC3: variableType = ShaderUniformVariableType::Vector3; break;
	// 		case GL_FLOAT_VEC4: variableType = ShaderUniformVariableType::Vector4; break;
	// 		case GL_FLOAT_MAT4: variableType = ShaderUniformVariableType::Matrix4; break;
	// 		default: variableType = ShaderUniformVariableType::Unknown; break;
	// 		}
	//
	// 		std::string variableName(name);
	//
	// 		const unsigned int location = getUniformLocation(variableName.c_str());
	//
	// 		uniformVariables.push_back({ variableName, variableType, location });
	// 	}
	// }

	void Shader::bindAttributes()
	{
		bindAttribute(0, "position");
		bindAttribute(1, "textureCoords");
	}

	
	void Shader::bindAttribute(int attribute, std::string variableName) const
	{
		glBindAttribLocation(programID, attribute, variableName.c_str());
	}

	int Shader::getUniformLocation(const GLchar* uniformName) const
	{
		GLint location = glGetUniformLocation(programID, uniformName);
		if (location == -1)
		{
			LOG_ERROR("Variable \"{0}\" not found in the shader code", uniformName);
			return -1;
		}
		
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