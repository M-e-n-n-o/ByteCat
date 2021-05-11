#pragma once

#include <vector>
#include "byteCat/render/Model.h"

namespace BC
{
	namespace Loader
	{
		RawModel LoadToVAO(std::vector<float>& positions, std::vector<int>& indices);
		void CleanUp();
	}
}
