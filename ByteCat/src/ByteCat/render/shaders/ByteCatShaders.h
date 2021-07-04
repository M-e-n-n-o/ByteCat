#pragma once

#include <string>

namespace BC
{
	namespace shaders
	{
		namespace standard
		{
			static std::string vertexShader = R"(
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

			static std::string fragmentShader = R"(
			#version 410

			in vec2 passTextureCoords;

			out vec4 outColor;

			uniform sampler2D textureSampler;

			
			void main(void)
			{
				outColor = texture(textureSampler, passTextureCoords);
			}
			)";
		}
	}
}
