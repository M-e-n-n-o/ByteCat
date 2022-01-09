#pragma once
#include "byteCat/graphics/renderer/RendererAPI.h"

namespace BC
{	
	struct RendererCommand
	{
		virtual ~RendererCommand() = default;
		
		virtual void execute(RendererAPI* rendererAPI) = 0;
	};

	struct SetViewPortCommand : RendererCommand
	{
	private:
		unsigned int x, y, width, height;
	
	public:
		SetViewPortCommand(unsigned int x, unsigned int y, unsigned int width, unsigned int height): x(x), y(y), width(width), height(height) {}

		void execute(RendererAPI* rendererAPI) override { rendererAPI->setViewport(x, y, width, height); }
	};
}
