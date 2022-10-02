#pragma once
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/RenderPass.h"

namespace BC
{
	namespace Graphics
	{
		class ShadowPass : public RenderPass
		{
		private:
			RendererAPI* m_rendererAPI;

		public:
			ShadowPass() : RenderPass("ShadowPass") {}

			void init(RendererAPI* rendererAPI) override
			{
				m_rendererAPI = rendererAPI;
			}

			void execute(std::vector<std::shared_ptr<Renderable>> renderables, std::shared_ptr<CameraData> cameraData, std::shared_ptr<LightingData> lightingData) override
			{
				
			}
		};
	}
}