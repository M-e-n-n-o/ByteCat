#include "bcpch.h"
#include "byteCat/graphics/renderer/RendererAPI.h"

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
	#include "platform/openGL/OpenGLRendererAPI.h"
#endif

namespace BC
{
	namespace Graphics
	{
		void RendererAPI::SetDepthTest(bool enable)
		{
			if (s_instance != nullptr)
			{
				s_instance->SetDepthTest(enable);
			}
		}

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

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
				case GraphicsAPI::OpenGL:
				case GraphicsAPI::OpenGLES:	LOG_INFO("Creating an OpenGL renderer"); s_instance = new Platform::OpenGLRendererAPI();
#endif
				}

				return s_instance;
			}

			return nullptr;
		}
	}
}
