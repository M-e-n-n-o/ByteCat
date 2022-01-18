#pragma once
#include "byteCat/graphics/renderer/RendererBase.h"

namespace BC
{
	class SimpleRenderer : public RendererBase
	{
	private:
		std::vector<Renderable> m_entities;
		
		RendererAPI* m_rendererAPI;
		SceneData m_sceneData;
	
	public:
		void init(RendererAPI* rendererAPI) override;
		void submit(const Renderable& renderable) override;
		void renderFrame(const SceneData& sceneData) override;
		
		bool supports(const GraphicsAPI& api) override;
		
		const std::string& getName() const override { return "SimpleRenderer"; }
	};
}
