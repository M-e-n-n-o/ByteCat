#include "bcpch.h"
#include "byteCat/entity-system/ModelStorage.h"
#include "byteCat/utils/ModelLoader.h"

namespace BC
{
	std::shared_ptr<VertexArray> ModelStorage::GetModel(std::string const& fileName, bool useStaticModel)
	{
		ModelData model;
		bool hasModel = HasModel(fileName, model);
		
		if (!hasModel)
		{
			std::vector<float> vertices;
			std::vector<unsigned int> indices;
			std::vector<float> normals;
			std::vector<float> textureCoords;
			bool success = ModelLoader::LoadModel(fileName, vertices, indices, normals, textureCoords);

			if (!success)
			{
				return nullptr;
			}

			std::shared_ptr<VertexArray> vao = CreateVAO(vertices, indices, textureCoords, normals);
			model = { fileName, vao, vertices, indices, textureCoords, normals };
			storage.push_back(model);
		}

		if (useStaticModel)
		{
			return model.vao;
		}

		return CreateVAO(model.vertices, model.indices, model.normals, model.textureCoords);
	}


	bool ModelStorage::HasModel(std::string const& fileName, ModelData& model)
	{
		for (ModelData& storagedModel : storage)
		{
			if (storagedModel.fileName == fileName)
			{
				model = storagedModel;
				return true;
			}
		}

		return false;
	}


	std::shared_ptr<VertexArray> ModelStorage::CreateVAO(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& textureCoords, std::vector<float>& normals)
	{
		std::shared_ptr<VertexArray> vao = VertexArray::Create();

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

		return vao;
	}


	std::shared_ptr<VertexArray> ModelStorage::AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned>& indices)
	{
		std::shared_ptr<VertexArray> vao = VertexArray::Create();

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), (unsigned)(sizeof(float) * vertices.size()));
		vertexBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), (unsigned)indices.size());
		vao->setIndexBuffer(indexBuffer);

		storage.push_back({ name, vao, vertices, indices });
		return vao;
	}

	std::shared_ptr<VertexArray> ModelStorage::AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& textureCoords)
	{
		std::shared_ptr<VertexArray> vao = VertexArray::Create();

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), (unsigned)(sizeof(float) * vertices.size()));
		vertexBuffer->setBufferType({ ShaderDataType::Float3 });
		vao->addVertexBuffer(vertexBuffer);

		std::shared_ptr<VertexBuffer> textureBuffer = VertexBuffer::Create(textureCoords.data(), (unsigned)(sizeof(float) * textureCoords.size()));
		textureBuffer->setBufferType({ ShaderDataType::Float2 });
		vao->addVertexBuffer(textureBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), (unsigned)indices.size());
		vao->setIndexBuffer(indexBuffer);

		storage.push_back({ name, vao, vertices, indices, textureCoords });
		return vao;
	}

	std::shared_ptr<VertexArray> ModelStorage::AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& textureCoords, std::vector<float>& normals)
	{
		std::shared_ptr<VertexArray> vao = CreateVAO(vertices, indices, textureCoords, normals);
		storage.push_back({ name, vao, vertices, indices, textureCoords, normals });
		return vao;
	}
}
