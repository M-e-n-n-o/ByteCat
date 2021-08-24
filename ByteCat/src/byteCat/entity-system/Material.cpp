#include "bcpch.h"
#include "byteCat/entity-system/Material.h"
#include "byteCat/utils/Storage.h"

namespace BC
{
	Material::Material(ByteCatShader const& shaderType, std::string const& texture2DFile): ObjectComponent()
	{
		shader = Shaders::Create(shaderType);
		setTexture(texture2DFile);
	}

	Material::Material(std::shared_ptr<Shader> shader, std::string const& texture2DFile): ObjectComponent()
	{
		this->shader = shader;
		setTexture(texture2DFile);
	}

	Material::Material(std::string& vertexShader, std::string& fragmentShader, std::string const& texture2DFile): ObjectComponent()
	{
		shader = Shader::Create(vertexShader, fragmentShader);
		setTexture(texture2DFile);
	}

	void Material::setTexture(std::string const& texture2DFile, unsigned int textureUnit)
	{
		if (texture2DFile.empty())
		{
			return;
		}

		std::string textureFile = texture2DFile; textureFile.insert(0, "res/");
		if (auto texture = Storage::GetTexture(textureFile); texture)
		{
			shader->setTexture(texture, textureUnit);
		}
	}

	void Material::setTexture(std::shared_ptr<Texture2D> texture2D, unsigned int textureUnit)
	{
		shader->setTexture(texture2D, textureUnit);
	}
}
