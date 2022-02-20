#include "bcpch.h"
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "platform/openGL/OpenGLRendererAPI.h"

namespace BC
{
	void RendererAPI::SetCullingMode(const CullingMode& mode)
	{
		if (s_instance != nullptr)
		{
			s_instance->setCullingMode(mode);
		}
	}

	RendererAPI* RendererAPI::Create(const GraphicsAPI& api)
	{
		static bool createdRendererAPI = false;
		
		if (!createdRendererAPI)
		{
			createdRendererAPI = true;
			
			switch (api)
			{
			case GraphicsAPI::None:		LOG_CRITICAL("GraphicsAPI::None is not a supported Graphics API"); return nullptr;
			case GraphicsAPI::OpenGL:	LOG_INFO("Creating an OpenGL renderer"); s_instance = new Platform::OpenGLRendererAPI();
			}

			return s_instance;
		}

		return nullptr;
	}
}
