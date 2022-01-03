#include "bcpch.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "platform/openGL/OpenGLShader.h"

namespace BC
{
	namespace Platform
	{
		OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : name(name)
		{
			const unsigned int vertexShaderID = loadShader(vertexSrc, GL_VERTEX_SHADER);
			const unsigned int fragmentShaderID = loadShader(fragmentSrc, GL_FRAGMENT_SHADER);

			programID = glCreateProgram();
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);

			glLinkProgram(programID);
			glValidateProgram(programID);

			glDetachShader(programID, vertexShaderID);
			glDetachShader(programID, fragmentShaderID);
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
		}

		OpenGLShader::~OpenGLShader()
		{
			glDeleteProgram(programID);
		}

		void OpenGLShader::bind() const
		{
			glUseProgram(programID);
		}

		void OpenGLShader::unbind() const
		{
			glUseProgram(0);
		}

		void OpenGLShader::loadInt(const std::string& name, int value)
		{
			GLint location = getUniformLocation(name);
			if (location != -1)
			{
				glUniform1i(location, value);
			}
		}

		void OpenGLShader::loadIntArray(const std::string& name, int* values, unsigned count)
		{
			GLint location = getUniformLocation(name);
			if (location != -1)
			{
				glUniform1iv(location, count, values);
			}
		}

		void OpenGLShader::loadFloat(const std::string& name, float value)
		{
			GLint location = getUniformLocation(name);
			if (location != -1)
			{
				glUniform1f(location, value);
			}
		}

		void OpenGLShader::loadVector2(const std::string& name, const glm::vec2& value)
		{
			GLint location = getUniformLocation(name);
			if (location != -1)
			{
				glUniform2fv(location, 1, glm::value_ptr(value));
			}
		}

		void OpenGLShader::loadVector3(const std::string& name, const glm::vec3& value)
		{
			GLint location = getUniformLocation(name);
			if (location != -1)
			{
				glUniform3fv(location, 1, glm::value_ptr(value));
			}
		}

		void OpenGLShader::loadVector4(const std::string& name, const glm::vec4& value)
		{
			GLint location = getUniformLocation(name);
			if (location != -1)
			{
				glUniform4fv(location, 1, glm::value_ptr(value));
			}
		}

		void OpenGLShader::loadMatrix4(const std::string& name, const glm::mat4& value)
		{
			GLint location = getUniformLocation(name);
			if (location != -1)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
			}
		}

		int OpenGLShader::getUniformLocation(const std::string& uniformName) const
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

		unsigned OpenGLShader::loadShader(const std::string& shader, int type) const
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

				LOG_ERROR("Shader error info:");
				for (std::vector<GLchar>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
				{
					std::cout << *i;
				}
				
				LOG_CRITICAL("Could not compile shader!");
			}

			return shaderID;
		}
	}
}
