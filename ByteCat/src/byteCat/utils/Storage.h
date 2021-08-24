#pragma once

#include <map>
#include "byteCat/render/vertex-object/VertexArray.h"
#include "byteCat/render/textures/Texture.h"

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
	 * Class Storage:
	 *			This class stores information about 3D models and 2D textures which can be retrieved when asked for.
	 */
	class Storage
	{
	private:
		inline static std::vector<ModelData> modelStorage;
		inline static std::map<std::string, std::shared_ptr<Texture2D>> texture2DStorage;

	public:
		// Model functions
		static std::shared_ptr<VertexArray> GetModel(std::string const& fileName, bool useStaticModel = true);

		static std::shared_ptr<VertexArray> AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned int>& indices);
		static std::shared_ptr<VertexArray> AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& textureCoords);
		static std::shared_ptr<VertexArray> AddToStorage(std::string const& name, std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& textureCoords, std::vector<float>& normals);

		// Texture functions
		static std::shared_ptr<Texture2D> GetTexture(std::string const& fileName, bool useStaticTexture = true);
	private:
		static bool HasModel(std::string const& fileName, ModelData& model);
		static bool HasTexture(std::string const& fileName, std::shared_ptr<Texture2D>& texture);

		static std::shared_ptr<VertexArray> CreateVAO(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& textureCoords, std::vector<float>& normals);
	};
}
