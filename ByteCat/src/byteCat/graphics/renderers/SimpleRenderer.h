#pragma once
#include "byteCat/graphics/renderers/Renderer.h"

namespace BC
{
	class SimpleRenderer : public RenderBase
	{
	private:
		RendererAPI* rendererAPI;
		SceneData sceneData;
	
	public:
		void startScene(RendererAPI* rendererAPI, const SceneData& sceneData) override;
		void setSceneData(const SceneData& sceneData) override { this->sceneData = sceneData; }
		void submit(const Renderable& renderable) override;
		void renderScene() override;
		
		bool supports(const GraphicsAPI& api) override;
		
		const std::string& getName() const override { return "SimpleRenderer"; }
	};
}
