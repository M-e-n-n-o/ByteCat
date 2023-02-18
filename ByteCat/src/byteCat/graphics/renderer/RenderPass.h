#pragma once
#include <memory>
#include "byteCat/graphics/renderer/Renderable.h"
#include "byteCat/graphics/renderer/CameraData.h"
#include "byteCat/graphics/renderer/LightingData.h"

namespace BC
{
	namespace Graphics
	{
		class RenderPass
		{
		protected:
			std::string m_name;

		public:
			RenderPass(const std::string& name): m_name(name) {}
			virtual ~RenderPass() = default;

			std::string getName() { return m_name; }

			virtual void init(RendererAPI* rendererAPI) = 0;
			virtual void execute(std::vector<std::shared_ptr<Renderable>>& renderables, std::shared_ptr<CameraData>& cameraData, std::shared_ptr<LightingData>& lightingData) = 0;
		};
	}
}