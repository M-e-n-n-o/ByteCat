#include "bcpch.h"
#include "byteCat/graphics/renderers/RendererAPI.h"
#include "platform/openGL/OpenGLRendererAPI.h"

namespace BC
{
	GraphicsAPI RendererAPI::graphicsAPI = GraphicsAPI::None;

	RendererAPI* RendererAPI::Create(const GraphicsAPI& api)
	{
		static bool createdRendererAPI = false;
		
		if (!createdRendererAPI)
		{
			createdRendererAPI = true;
			graphicsAPI = api;

			switch (graphicsAPI)
			{
			case GraphicsAPI::None:		LOG_CRITICAL("GraphicsAPI::None is not a supported Graphics API"); return nullptr;
			case GraphicsAPI::OpenGL:	LOG_INFO("Selected OpenGL as Graphics API"); return new Platform::OpenGLRendererAPI();
			}
		}

		return nullptr;
	}
}
