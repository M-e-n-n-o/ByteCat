#pragma once

#include "byteCat/entity-system/GameObject.h"
#include "byteCat/render/shaders/ByteCatShaders.h"

namespace BC
{
	/*
	 * Class Material:
	 *		This class holds a shader which is needed to render a VertexArray (object on the screen)
	 */
	class Material : public ObjectComponent
	{
	private:
		std::shared_ptr<Shader> shader;

	public:
		Material(ByteCatShader const& shaderType, std::string const& texture2DFile = "");
		Material(std::shared_ptr<Shader> shader, std::string const& texture2DFile = "");
		Material(std::string& vertexShader, std::string& fragmentShader, std::string const& texture2DFile = "");

		void setShader(std::shared_ptr<Shader> newShader) { shader = newShader; }
		std::shared_ptr<Shader>& getShader() { return shader; }

		void setTexture(std::string const& texture2DFile, unsigned int textureUnit = 0);
		void setTexture(std::shared_ptr<Texture2D> texture2D, unsigned int textureUnit = 0);
	};
}
