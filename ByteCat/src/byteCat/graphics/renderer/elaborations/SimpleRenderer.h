#pragma once
#include "byteCat/graphics/renderer/RendererBase.h"

namespace BC
{
	class SimpleRenderer : public RenderBase
	{
	private:
		std::vector<Renderable> entities;
		
		RendererAPI* rendererAPI;
		SceneData sceneData;
	
	public:
		void init(RendererAPI* rendererAPI) override;
		void submit(const Renderable& renderable) override;
		void renderFrame(const SceneData& sceneData) override;
		
		bool supports(const GraphicsAPI& api) override;
		
		const std::string& getName() const override { return "SimpleRenderer"; }
	};
}
