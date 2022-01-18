#include "bcpch.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "platform/openGL/OpenGLShader.h"

#include "platform/CommandExecutor.h"

namespace BC
{
	namespace Platform
	{
		OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_name(name)
		{			
			const unsigned int vertexShaderID = loadShader(vertexSrc, GL_VERTEX_SHADER);
			const unsigned int fragmentShaderID = loadShader(fragmentSrc, GL_FRAGMENT_SHADER);

			m_programID = glCreateProgram();
			glAttachShader(m_programID, vertexShaderID);
			glAttachShader(m_programID, fragmentShaderID);

			glLinkProgram(m_programID);

			int success;
			char infoLog[512];
			glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
			if (!success) {
				//glGetProgramInfoLog(programID, 512, NULL, infoLog);
				LOG_CRITICAL("Could not link shader program: {0}", name);
				//LOG_TEXT_LONG(infoLog);
			}
			
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
		}

		OpenGLShader::~OpenGLShader()
		{
			glDeleteProgram(m_programID);
		}

		void OpenGLShader::bind() const
		{
			CommandExecutor::PushCommand([id = m_programID]()
			{
				glUseProgram(id);
			});
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

		void OpenGLShader::linkUniformBuffer(const std::string& bufferName, unsigned bindingIndex)
		{
			unsigned int uniformBlockIndex = glGetUniformBlockIndex(m_programID, bufferName.c_str());
			glUniformBlockBinding(m_programID, uniformBlockIndex, bindingIndex);
		}

		int OpenGLShader::getUniformLocation(const std::string& uniformName) const
		{
			if (uniformLocationCache.find(uniformName) != uniformLocationCache.end())
			{
				return uniformLocationCache[uniformName];
			}

			GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
			if (location == -1)
			{
				LOG_ERROR("Variable \"{0}\" not found in the shader {1}", uniformName, m_name);
				return -1;
			}

			uniformLocationCache[uniformName] = location;

			return location;
		}

		unsigned OpenGLShader::loadShader(const std::string& shader, int type) const
		{
			const GLchar* shaderText = shader.c_str();
			const GLuint shaderID = glCreateShader(type);
			glShaderSource(shaderID, 1, &shaderText, nullptr);
			glCompileShader(shaderID);

			GLint succes = 0;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
			if (succes == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> errorLog(maxLength);
				glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

				LOG_ERROR("Shader error info: {0}", m_name);
				std::stringstream log;
				for (std::vector<GLchar>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
				{
					log << *i;
				}

				LOG_TEXT_LONG(log.str());
				
				LOG_CRITICAL("Could not compile shader: {0}", m_name);
			}

			return shaderID;
		}
	}
}
