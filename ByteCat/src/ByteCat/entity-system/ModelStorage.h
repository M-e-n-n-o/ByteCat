#pragma once

#include "byteCat/render/vertex-object/VertexArray.h"

namespace BC
{
	// A structure with data about a 3D model which has been loaded from a file
	struct ModelData
	{
		std::string fileName;
		
		std::shared_ptr<VertexArray> vao;
		
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		std::vector<float> textureCoords;
		std::vector<float> normals;
	};

	/*
	 * Class ModelStorage:
	 *			This class stores information about 3D models which can be retrieved when asked
	 */
	class ModelStorage
	{
	private:
		inline static std::vector<ModelData> storage;

	public:
		static std::shared_ptr<VertexArray> GetModel(std::string const& fileName, bool useStaticModel = true);

		static std::shared_ptr<VertexArray> AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned int>& indices);
		static std::shared_ptr<VertexArray> AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& textureCoords);
		static std::shared_ptr<VertexArray> AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& textureCoords, std::vector<float>& normals);
	private:
		static bool HasModel(std::string const& fileName, ModelData& model);

		static std::shared_ptr<VertexArray> CreateVAO(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& textureCoords, std::vector<float>& normals);
	};
}
