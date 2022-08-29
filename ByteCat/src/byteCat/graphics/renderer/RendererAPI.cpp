#include "bcpch.h"
#include "byteCat/graphics/renderer/RendererAPI.h"

#ifdef BC_PLATFORM_PC
	#include "platform/openGL/OpenGLRendererAPI.h"
#elif defined(BC_PLATFORM_MOBILE)
	#include "platform/mobile/MobileRendererAPI.h"
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

#ifdef BC_PLATFORM_PC
				case GraphicsAPI::OpenGL:	LOG_INFO("Creating an OpenGL renderer"); s_instance = new Platform::OpenGLRendererAPI();
#elif defined(BC_PLATFORM_MOBILE)
				case GraphicsAPI::OpenGLES:	LOG_INFO("Creating an OpenGLES renderer"); s_instance = new Platform::MobileRendererAPI();
#endif
				}

				return s_instance;
			}

			return nullptr;
		}
	}
}
