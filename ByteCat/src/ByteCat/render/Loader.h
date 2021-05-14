#pragma once

#include <vector>
#include <string>
#include "byteCat/render/models/Model.h"

namespace BC
{
	namespace Loader
	{
		RawModel LoadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<int>& indices);

		unsigned int LoadTexture(std::string fileName);
		
		void CleanUp();
	}
}
