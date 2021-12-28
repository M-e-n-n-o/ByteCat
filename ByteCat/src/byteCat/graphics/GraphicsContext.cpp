#include "bcpch.h"
#include "byteCat/graphics/GraphicsContext.h"

#include "platform/openGL/OpenGLGraphicsContext.h"

namespace BC
{
	GraphicsContext* GraphicsContext::Create(void* window, GraphicsAPI api)
	{
		switch (api)
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected");		return nullptr;
		case GraphicsAPI::OpenGL:	LOG_INFO("Selected OpenGL as Graphics API");	return new Platform::OpenGLGraphicsContext((GLFWwindow*)window);
		}

		LOG_CRITICAL("Unknown Graphics API selected");
		return nullptr;
	}
}
