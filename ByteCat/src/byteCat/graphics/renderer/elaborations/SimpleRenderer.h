#pragma once
#include "byteCat/graphics/renderer/BaseRenderer.h"

namespace BC
{
	class SimpleRenderer : public BaseRenderer
	{
	private:
		std::vector<Renderable> m_entities;
		
		RendererAPI* m_rendererAPI;
		SceneData m_sceneData;
	
	public:
		void init(RendererAPI* rendererAPI) override;
		void submit(const Renderable& renderable) override;
		void setSceneData(const SceneData& sceneData) override;
		void renderFrame() override;
		
		bool supports(const GraphicsAPI& api) override;
		
		const std::string& getName() const override { return "SimpleRenderer"; }
	};
}
