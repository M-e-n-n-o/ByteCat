#pragma once

namespace BC
{
	enum class CullingMode
	{
		None,
		Front,
		Back,
		FrontAndBack
	};

	enum class RenderLayer
	{
		Opaque,
		Transparent
	};
}
