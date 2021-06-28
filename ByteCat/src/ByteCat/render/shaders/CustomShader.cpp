#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/shaders/CustomShader.h"

namespace BC
{
	CustomShader::CustomShader(std::string& vertexShader, std::string& fragmentShader) : ShaderProgram(vertexShader, fragmentShader)
	{
	}

	void CustomShader::loadUniformVariable(std::string& variableName, ShaderUniformVariableValue value)
	{
		for (auto& variable : uniformVariables)
		{
			if (variable.name == variableName)
			{
				switch (variable.type)
				{
					//TODO value inladen in shader
				}

				return;
			}
		}
	}

	void CustomShader::getAllUniformLocations()
	{
		int totalVariables;
		glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &totalVariables);

		for (int i = 0; i < totalVariables; i++)
		{
			int length;
			int size;
			GLenum type;
			char* name;
			glGetActiveUniform(programID, i, 25, &length, &size, &type, name);

			ShaderUniformVariableType variableType;
			switch (type)
			{
			case GL_FLOAT: variableType = ShaderUniformVariableType::Float; break;
			case GL_INT: variableType = ShaderUniformVariableType::Int; break;
			case GL_FLOAT_VEC2: variableType = ShaderUniformVariableType::Vector2; break;
			case GL_FLOAT_VEC3: variableType = ShaderUniformVariableType::Vector3; break;
			case GL_FLOAT_VEC4: variableType = ShaderUniformVariableType::Vector4; break;
			case GL_FLOAT_MAT4: variableType = ShaderUniformVariableType::Matrix4; break;
			default: variableType = ShaderUniformVariableType::Unknown; break;
			}

			std::string variableName(name);

			const unsigned int location = getUniformLocation(variableName.c_str());

			uniformVariables.push_back({ variableName, variableType, location });
		}
	}

	void CustomShader::bindAttributes()
	{
		bindAttribute(0, "position");
		bindAttribute(1, "textureCoords");
	}
}
