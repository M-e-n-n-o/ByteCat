#include "bcpch.h"
#include "byteCat/render/shaders/ByteCatShaders.h"

namespace BC
{
	const std::string StandardShader::vertexShader = R"(
		#version 410

		layout (location = 0) in vec3 position;
		layout (location = 1) in vec2 textureCoords;

		out vec2 passTextureCoords;

		uniform mat4 modelMatrix;
		
		void main(void)
		{
			gl_Position = modelMatrix * vec4(position, 1.0);
			passTextureCoords = textureCoords;
		}
	)";

	const std::string StandardShader::fragmentShader = R"(
		#version 410

		in vec2 passTextureCoords;

		out vec4 outColor;

		uniform sampler2D textureSampler;

		
		void main(void)
		{
			outColor = texture(textureSampler, passTextureCoords);
		}
	)";


	StandardShader::StandardShader(): Shader(vertexShader, fragmentShader)
	{
		// Load in optional uniform variables that will always stay the same
	}
}
