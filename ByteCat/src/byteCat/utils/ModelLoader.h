#pragma once

#include <vector>

namespace BC
{
	namespace ModelLoader
	{
		// Call this function to load a 3D model from a file.
		bool LoadModel(std::string const& filePath, std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& normals, std::vector<float>& textureCoords);
	}
}