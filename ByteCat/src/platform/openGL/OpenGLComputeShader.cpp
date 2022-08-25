#ifdef BC_PLATFORM_PC
#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLComputeShader.h"
#include "platform/openGL/Helper.h"
#include "byteCat/utils/FileIO.h"

namespace BC
{
	namespace Platform
	{		
		OpenGLComputeShader::OpenGLComputeShader(const std::string& name, const std::string& computeSrc, bool isFilePath): m_name(name)
		{
			std::string computeShader = computeSrc;

			if (isFilePath)
			{
				computeShader.insert(0, BC_ASSETS_FOLDER);
				computeShader = Utils::FileIO::ReadFileIntoString(computeShader);
			}

			const unsigned int computeShaderID = loadShader(computeShader, GL_COMPUTE_SHADER);

			m_programID = glCreateProgram();
			glAttachShader(m_programID, computeShaderID);

			glLinkProgram(m_programID);

			int success;
			char infoLog[512];
			glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
			if (!success) 
			{
				//glGetProgramInfoLog(programID, 512, NULL, infoLog);
				LOG_ERROR("Could not link shader program: %s", name.c_str());
				//LOG_TEXT_LONG(infoLog);
			}

			LOG_INFO("Finished compiling compute shader: %s", name.c_str());

			// Compute shader debug info
			// int work_grp_cnt[3];
			// glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
			// glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
			// glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);
			// LOG_INFO("Max global work group count: {0}, {1}, {2}", work_grp_cnt[0], work_grp_cnt[1], work_grp_cnt[2]);
			//
			// int work_grp_size[3];
			// glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
			// glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
			// glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);
			// LOG_INFO("Max local work group size: {0}, {1}, {2}", work_grp_size[0], work_grp_size[1], work_grp_size[2]);
			//
			// int work_grp_inv;
			// glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
			// LOG_INFO("Max local work group invocations: {0}", work_grp_inv);
			
			glDeleteShader(computeShaderID);
		}

		OpenGLComputeShader::~OpenGLComputeShader()
		{
			glDeleteProgram(m_programID);
		}

		void OpenGLComputeShader::compute(unsigned numberOfGroupsX, unsigned numberOfGroupsY, unsigned numberOfGroupsZ)
		{			
			glUseProgram(m_programID);
			glDispatchCompute(numberOfGroupsX, numberOfGroupsY, numberOfGroupsZ);
		}

		void OpenGLComputeShader::waitToFinish()
		{
			glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		}

		void OpenGLComputeShader::setOutputTexture(std::shared_ptr<Graphics::Texture> texture, unsigned int textureUnit)
		{
			glBindImageTexture(textureUnit, texture->getId(), 0, GL_FALSE, 0, GL_WRITE_ONLY, TextureFormatToOpenGLInternalFormat(texture->getFormat()));
		}

		unsigned OpenGLComputeShader::loadShader(const std::string& shader, int type) const
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

				LOG_TEXT_LONG(log.str());

				LOG_ERROR("Could not compile shader: %s", m_name.c_str());
			}

			return shaderID;
		}
	}
}
#endif