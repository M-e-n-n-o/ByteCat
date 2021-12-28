#include "bcpch.h"
#include "byteCat/graphics/GraphicsAPI.h"

namespace BC
{
	GraphicsAPI RendererAPI::graphicsAPI = GraphicsAPI::None;

	void RendererAPI::SetGraphicsAPI(GraphicsAPI api)
	{
		if (graphicsAPI != GraphicsAPI::None)
		{
			LOG_WARN("Cannot change the GraphicsAPI again after choosing the first time!");
			return;
		}

		LOG_INFO("A GraphicsAPI has been chosen :D");

		graphicsAPI = api;
	}
}
