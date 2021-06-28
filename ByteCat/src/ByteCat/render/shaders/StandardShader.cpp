#include "bcpch.h"
#include "byteCat/render/shaders/StandardShader.h"

namespace BC
{
	static std::string vertexShader = R"(
	#version 400 core

	in vec3 position;
	in vec2 textureCoords;

	out vec2 passTextureCoords;

	
	void main(void)
	{
		gl_Position = vec4(position, 1.0);
		passTextureCoords = textureCoords;
	}
	)";

	static std::string fragmentShader = R"(
	#version 400 core

	in vec2 passTextureCoords;

	out vec4 outColor;

	uniform sampler2D textureSampler;

	
	void main(void)
	{
		outColor = texture(textureSampler, passTextureCoords);
	}
	)";

	StandardShader::StandardShader() : ShaderProgram(vertexShader, fragmentShader) { }

	void StandardShader::getAllUniformLocations()
	{
		
	}

	void StandardShader::bindAttributes()
	{
		bindAttribute(0, "position");
		bindAttribute(1, "textureCoords");
	}
}
