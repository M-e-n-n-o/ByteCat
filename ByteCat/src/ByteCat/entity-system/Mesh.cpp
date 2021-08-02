#include "bcpch.h"
#include "byteCat/entity-system/Mesh.h"
#include "byteCat/entity-system/Material.h"
#include "byteCat/render/Renderer.h"
#include "byteCat/utils/ModelLoader.h"

namespace BC
{
	Mesh::Mesh(): ObjectComponent()
	{
		vao = VertexArray::Create();
	}

	Mesh::Mesh(std::string const& fileName)
	{
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		std::vector<float> normals;
		std::vector<float> textureCoords;
		ModelLoader::LoadModel(fileName, vertices, indices, normals, textureCoords);

		init(vertices, indices, textureCoords);
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
		init(vertices, indices, textureCoords);
	}

	void Mesh::init(std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& textureCoords)
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


	void MeshRenderer::prepareRender(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
	{	
		std::shared_ptr<Shader> shader = gameObject->getComponent<Material>()->getShader();
		
		shader->loadMatrix4("modelMatrix", gameObject->getModelMatrix());
		shader->bindTextures();
	}

	void MeshRenderer::finishRender()
	{

	}
}
