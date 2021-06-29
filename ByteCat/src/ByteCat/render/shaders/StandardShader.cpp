#include "bcpch.h"
#include "byteCat/render/shaders/StandardShader.h"

namespace BC
{
	static std::string vertexShader = R"(
	#version 400 core

	in vec3 position;
	in vec2 textureCoords;

	out vec2 passTextureCoords;

	uniform mat4 modelMatrix;
	
	void main(void)
	{
		gl_Position = modelMatrix * vec4(position, 1.0);
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


	StandardShader::StandardShader(Texture2D& texture): Shader(vertexShader, fragmentShader), mainTexture(&texture)
	{
		setTextures([this]()
		{
			mainTexture->bind();
		});
	}
}
