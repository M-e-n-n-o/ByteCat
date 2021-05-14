#pragma once

namespace BC
{
	struct RawModel
	{
		unsigned int vaoID;
		unsigned int vertexCount;
	};

	struct ModelTexture
	{
		unsigned int textureID;
	};

	struct TexturedModel
	{
		RawModel rawModel;
		ModelTexture texture;
	};
}
