#pragma once

#include <vector>
#include <string>
#include "byteCat/render/models/Mesh.h"

namespace BC
{
	namespace Loader
	{
		VAO LoadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<int>& indices);

		unsigned int Load2DTexture(std::string fileName, int& width, int& height);
	}
}
