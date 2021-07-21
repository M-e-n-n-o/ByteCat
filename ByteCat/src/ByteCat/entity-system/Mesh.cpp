#include "bcpch.h"
#include "byteCat/entity-system/Mesh.h"
#include "byteCat/entity-system/Material.h"

namespace BC
{
	Mesh::Mesh(): ObjectComponent()
	{
		vao = VertexArray::Create();
	}

	Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices) : ObjectComponent()
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


	// ------------------------------------------------------------------------------------------------------------
	// ------------------------------------- Mesh Renderer --------------------------------------------------------


	VertexArray* MeshRenderer::prepareRender(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
	{
		auto mat = gameObject->getComponentOfType<Material>();
		if (mat == nullptr)
		{
			LOG_ERROR("{0} cannot be rendered because it does not have a material", gameObject->name);
			return nullptr;
		}

		auto mesh = gameObject->getComponentOfType<Mesh>();
		if (mesh == nullptr)
		{
			LOG_ERROR("{0} cannot be rendered because it does not have a mesh", gameObject->name);
			return nullptr;
		}
		
		std::shared_ptr<Shader> shader = mat->getShader();
		
		shader->bind();
		shader->loadMatrix4("modelMatrix", gameObject->getModelMatrix());
		shader->loadMatrix4("projectionMatrix", projectionMatrix);
		shader->loadMatrix4("viewMatrix", viewMatrix);
		mesh->getVao()->bind();
		shader->bindTextures();
		
		return mesh->getVao().get();
	}

	void MeshRenderer::finishRender()
	{
		auto mat = gameObject->getComponentOfType<Material>();
		auto mesh = gameObject->getComponentOfType<Mesh>();
		
		mesh->getVao()->unbind();
		mat->getShader()->unbind();
	}
}
