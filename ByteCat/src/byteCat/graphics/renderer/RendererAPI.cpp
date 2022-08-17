#include "bcpch.h"
#include "byteCat/graphics/renderer/RendererAPI.h"

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
#include "platform/openGL/OpenGLRendererAPI.h"
#endif

namespace BC
{
	namespace Graphics
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

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
				case GraphicsAPI::OpenGL:	LOG_INFO("Creating an OpenGL renderer"); s_instance = new Platform::OpenGLRendererAPI();
#endif
				}

				return s_instance;
			}

			return nullptr;
		}
	}
}
