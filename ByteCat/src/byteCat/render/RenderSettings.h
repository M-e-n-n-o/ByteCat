#pragma once

namespace BC
{
	/*
	 * A enum class for all the different render modes.
	 *		-Filled to render objects normally.
	 *		-Wireframe to not render any faces.
	 */
	enum class RenderMode
	{
		Filled,
		Wireframe
	};

	/*
	 * A enum class for the types of culling.
	 *		-None to render all faces.
	 *		-Back to not render the back faces
	 *		-Front to not render the front faces
	 */
	enum class CullingMode
	{
		None,
		Back,
		Front
	};
}