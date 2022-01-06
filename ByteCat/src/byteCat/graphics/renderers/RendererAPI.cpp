#include "bcpch.h"
#include "byteCat/graphics/renderers/RendererAPI.h"
#include "platform/openGL/OpenGLRendererAPI.h"

namespace BC
{
	RendererAPI* RendererAPI::Create(const GraphicsAPI& api)
	{
		static bool createdRendererAPI = false;
		
		if (!createdRendererAPI)
		{
			createdRendererAPI = true;
			//graphicsAPI = api;

			switch (api)
			{
			case GraphicsAPI::None:		LOG_CRITICAL("GraphicsAPI::None is not a supported Graphics API"); return nullptr;
			case GraphicsAPI::OpenGL:	LOG_INFO("Creating an OpenGL renderer"); return new Platform::OpenGLRendererAPI();
			}
		}

		return nullptr;
	}
}
