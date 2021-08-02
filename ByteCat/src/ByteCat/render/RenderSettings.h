#pragma once

namespace BC
{
	/*
	 * A enum class for all the different render modes
	 */
	enum class RenderMode
	{
		Filled,
		Wireframe
	};


	enum class RenderCulling
	{
		None,
		Back,
		Front
	};
}