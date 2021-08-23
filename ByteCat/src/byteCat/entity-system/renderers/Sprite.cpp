#include "bcpch.h"
#include "byteCat/entity-system/renderers/Sprite.h"
#include "byteCat/entity-system/Material.h"

namespace BC
{
	Sprite::Sprite(std::string const& fileName)
	{
		setTexture(fileName);
	}

	Sprite::Sprite(std::shared_ptr<Texture2D>& texture)
	{
		setTexture(texture);
	}

	void Sprite::setTexture(std::string const& fileName)
	{
		std::string file = fileName; file.insert(0, "res/");
		
		this->texture = Texture2D::Create(file);
		this->vao = generateVao(texture->getWidth(), texture->getHeight());
	}

	void Sprite::setTexture(std::shared_ptr<Texture2D>& texture)
	{
		this->texture = texture;
		this->vao = generateVao(texture->getWidth(), texture->getHeight());
	}

	void Sprite::onAttach()
	{
		Material* mat = gameObject->getComponent<Material>();
		if (mat == nullptr)
		{
			LOG_WARN("Add a material to {0} before adding a sprite component!");
			return;
		}

		mat->getShader()->setTexture(this->texture);
	}

	std::shared_ptr<VertexArray> Sprite::generateVao(unsigned width, unsigned height) const
	{
		std::shared_ptr<VertexArray> vao = VertexArray::Create();

		float x = width / 2.0f;
		float y = height / 2.0f;
		
		std::vector<float> vertices =
		{
			-x, y, 0,
			-x, -y, 0,
			x, -y, 0,
			x, y, 0
		};

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), (unsigned)(sizeof(float) * vertices.size()));
		vertexBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(vertexBuffer);

		std::vector<float> textureCoords =
		{
			0, 0,
			0, 1,
			1, 1,
			1, 0
		};
		
		std::shared_ptr<VertexBuffer> textureBuffer = VertexBuffer::Create(textureCoords.data(), (unsigned)(sizeof(float) * textureCoords.size()));
		textureBuffer->setBufferType({ ShaderDataType::Float2 });
		vao->addVertexBuffer(textureBuffer);

		std::vector<unsigned int> indices =
		{
			0, 1, 3,
			3, 1, 2
		};
		
		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), (unsigned)indices.size());
		vao->setIndexBuffer(indexBuffer);

		return vao;
	}


	// ------------------------------------------------------------------------------------------------------------
	// ------------------------------------ Rendering stuff -------------------------------------------------------
	

	void Sprite::prepareRender(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
	{
		std::shared_ptr<Shader> shader = gameObject->getComponent<Material>()->getShader();

		shader->loadMatrix4("modelMatrix", gameObject->getModelMatrix());
		shader->bindTextures();
	}
}
