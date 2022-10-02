#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
#include "bcpch.h"
#include <glm/gtc/type_ptr.hpp>
#include "platform/openGL/OpenGLShader.h"
#include "byteCat/utils/FileIO.h"

#if defined(BC_PLATFORM_PC)
	#include <glad/glad.h>
#elif defined(BC_PLATFORM_MOBILE)
	#include <glfm.h>
#endif

namespace BC
{
	namespace Platform
	{		
		OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, bool isFilePath) : m_name(name)
		{
			std::string vertexShader = vertexSrc;
			std::string fragmentShader = fragmentSrc;
			
			if (isFilePath)
			{
				// vertexShader.insert(0, BC_ASSETS_FOLDER);
				vertexShader = Utils::FileIO::ReadFileIntoString(vertexShader);
				
				// fragmentShader.insert(0, BC_ASSETS_FOLDER);
				fragmentShader = Utils::FileIO::ReadFileIntoString(fragmentShader);
			}
			
			const unsigned int vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
			const unsigned int fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);

			m_programID = glCreateProgram();
			glAttachShader(m_programID, vertexShaderID);
			glAttachShader(m_programID, fragmentShaderID);

			glLinkProgram(m_programID);

			int success;
			char infoLog[512];
			glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
			if (!success) 
			{
				LOG_ERROR("Could not link shader program: %s", name.c_str());
			}

			LOG_INFO("Finished compiling shader program: %s", name.c_str());

			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			glUseProgram(m_programID);
		}

		OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc, bool isFilePath)
		{
#if defined(BC_PLATFORM_PC)
			std::string vertexShader = vertexSrc;
			std::string geometryShader = geometrySrc;
			std::string fragmentShader = fragmentSrc;

			if (isFilePath)
			{
				//vertexShader.insert(0, BC_ASSETS_FOLDER);
				vertexShader = Utils::FileIO::ReadFileIntoString(vertexShader);

				//geometryShader.insert(0, BC_ASSETS_FOLDER);
				geometryShader = Utils::FileIO::ReadFileIntoString(geometryShader);
				
				//fragmentShader.insert(0, BC_ASSETS_FOLDER);
				fragmentShader = Utils::FileIO::ReadFileIntoString(fragmentShader);
			}

			const unsigned int vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
			const unsigned int geometryShaderID = loadShader(geometryShader, GL_GEOMETRY_SHADER);
			const unsigned int fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);

			m_programID = glCreateProgram();
			glAttachShader(m_programID, vertexShaderID);
			glAttachShader(m_programID, geometryShaderID);
			glAttachShader(m_programID, fragmentShaderID);

			glLinkProgram(m_programID);

			int success;
			char infoLog[512];
			glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
			if (!success) 
			{
				LOG_ERROR("Could not link shader program: %s", name.c_str());
			}

			LOG_INFO("Finished compiling shader program: %s", name.c_str());

			glDeleteShader(vertexShaderID);
			glDeleteShader(geometryShaderID);
			glDeleteShader(fragmentShaderID);

			glUseProgram(m_programID);
#endif
		}

		OpenGLShader::~OpenGLShader()
		{
			glDeleteProgram(m_programID);
		}

		void OpenGLShader::bind() const
		{
			glUseProgram(m_programID);
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

		void OpenGLShader::loadVector3Array(const std::string& name, const std::vector<glm::vec3>& values)
		{
			for (int i = 0; i < values.size(); i++)
			{
				GLint location = getUniformLocation(name + "[" + std::to_string(i) + "]");
				glUniform3fv(location, 1, glm::value_ptr(values[i]));
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

		void OpenGLShader::addTexture(const char* textureName, std::shared_ptr<Graphics::Texture> texture)
		{
			if (std::find(m_textures.begin(), m_textures.end(), texture) != m_textures.end())
			{
				return;
			}

			glUseProgram(m_programID);

			loadInt(textureName, m_textures.size());

			if (texture != nullptr)
			{
				m_textures.push_back(texture);
			}
		}

		void OpenGLShader::activateTextures()
		{
			for (int i = 0; i < m_textures.size(); i++)
			{
				m_textures[i]->bind(i);
			}
		}

		int OpenGLShader::getUniformLocation(const std::string& uniformName) const
		{
			if (m_uniformLocationCache.find(uniformName) != m_uniformLocationCache.end())
			{
				return m_uniformLocationCache[uniformName];
			}

			GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
			if (location == -1)
			{
				if (uniformName.rfind("_", 0) != 0)
				{
					LOG_ERROR("Variable \"%s\" not found in the shader %s", uniformName.c_str(), m_name.c_str());
				}
				return -1;
			}

			m_uniformLocationCache[uniformName] = location;

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

				LOG_ERROR("Shader error info: %s", m_name.c_str());
				std::stringstream log;
				for (std::vector<GLchar>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
				{
					log << *i;
				}

				LOG_TEXT_LONG(log.str().c_str());
				
				LOG_ERROR("Could not compile shader: %s", m_name.c_str());
			}

			return shaderID;
		}
	}
}
#endif