#pragma once

#include "byteCat/graphics/GraphicsAPI.h"

namespace BC
{	
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void init() = 0;
		virtual void swapBuffers() = 0;

		static GraphicsContext* Create(void* window, GraphicsAPI api);
	};
}
