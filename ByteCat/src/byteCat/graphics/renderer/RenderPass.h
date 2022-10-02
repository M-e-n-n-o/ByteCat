#pragma once
#include <memory>
#include "byteCat/graphics/renderer/Renderable.h"

namespace BC
{
	namespace Graphics
	{
		class RenderPass
		{
		public:
			RenderPass() = default;
			virtual ~RenderPass() = default;

			virtual void init(RendererAPI* rendererAPI) = 0;
			virtual void execute(std::vector<std::shared_ptr<Renderable>> renderables, std::shared_ptr<CameraData> cameraData) = 0;
		};
	}
}