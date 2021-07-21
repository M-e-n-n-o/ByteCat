#pragma once

#include <vector>

namespace BC
{
	namespace ModelLoader
	{
		bool LoadModel(std::string filePath, std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& normals, std::vector<float>& textureCoords);
	}
}