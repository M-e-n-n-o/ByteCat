#include "bcpch.h"
#include "byteCat/entity-system/renderers/Mesh.h"
#include "byteCat/entity-system/Material.h"
#include "byteCat/render/Renderer.h"
#include "byteCat/entity-system/ModelStorage.h"


namespace BC
{
	Mesh::Mesh()
	{
		vao = VertexArray::Create();
	}

	Mesh::Mesh(std::shared_ptr<VertexArray>& vao)
	{
		this->vao = vao;
	}

	Mesh::Mesh(std::string const& fileName, bool useStaticModel)
	{
		this->vao = ModelStorage::GetModel(fileName, useStaticModel);
	}

	Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices)
	{
		vao = VertexArray::Create();

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), (unsigned)(sizeof(float) * vertices.size()));
		vertexBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), (unsigned)indices.size());
		vao->setIndexBuffer(indexBuffer);
	}

	Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& textureCoords)
	{
		vao = VertexArray::Create();

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), (unsigned)(sizeof(float) * vertices.size()));
		vertexBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(vertexBuffer);

		std::shared_ptr<VertexBuffer> textureBuffer = VertexBuffer::Create(textureCoords.data(), (unsigned)(sizeof(float) * textureCoords.size()));
		textureBuffer->setBufferType({ ShaderDataType::Float2 });
		vao->addVertexBuffer(textureBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), (unsigned)indices.size());
		vao->setIndexBuffer(indexBuffer);
	}

	Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& textureCoords, std::vector<float>& normals)
	{
		vao = VertexArray::Create();

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), (unsigned)(sizeof(float) * vertices.size()));
		vertexBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(vertexBuffer);

		std::shared_ptr<VertexBuffer> textureBuffer = VertexBuffer::Create(textureCoords.data(), (unsigned)(sizeof(float) * textureCoords.size()));
		textureBuffer->setBufferType({ ShaderDataType::Float2 });
		vao->addVertexBuffer(textureBuffer);

		std::shared_ptr<VertexBuffer> normalBuffer = VertexBuffer::Create(normals.data(), (unsigned)(sizeof(float) * normals.size()));
		normalBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(normalBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), (unsigned)indices.size());
		vao->setIndexBuffer(indexBuffer);
	}


	// ------------------------------------------------------------------------------------------------------------
	// ------------------------------------ Rendering stuff -------------------------------------------------------


	void Mesh::prepareRender(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
	{	
		std::shared_ptr<Shader> shader = gameObject->getComponent<Material>()->getShader();
		
		shader->loadMatrix4("modelMatrix", gameObject->getModelMatrix());
		shader->bindTextures();
	}
}
