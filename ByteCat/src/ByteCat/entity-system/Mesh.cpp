#include "bcpch.h"
#include "byteCat/entity-system/Mesh.h"

namespace BC
{
	Mesh::Mesh(): ObjectComponent("Mesh")
	{
		vao = VertexArray::Create();
	}

	Mesh::Mesh(float vertices[], unsigned int sizeV, unsigned int indices[], unsigned int sizeI): ObjectComponent("Mesh")
	{
		vao = VertexArray::Create();

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeV);
		vertexBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeI / sizeof(unsigned int));
		vao->setIndexBuffer(indexBuffer);
	}

	Mesh::Mesh(float vertices[], unsigned int sizeV, unsigned int indices[], unsigned int sizeI, float textureCoords[], unsigned int sizeT): ObjectComponent("Mesh")
	{
		vao = VertexArray::Create();
		
		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeV);
		vertexBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(vertexBuffer);

		std::shared_ptr<VertexBuffer> textureBuffer = VertexBuffer::Create(textureCoords, sizeT);
		textureBuffer->setBufferType({ ShaderDataType::Float2 });
		vao->addVertexBuffer(textureBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeI / sizeof(unsigned int));
		vao->setIndexBuffer(indexBuffer);
	}
}
