#pragma once
#include "byteCat/graphics/renderer/SubmissionRenderer.h"

namespace BC
{
	class SimpleRenderer : public SubmissionRenderer
	{
	private:
		std::vector<Renderable> m_entities;

		//int m_transparentIndex = 0;
		
		RendererAPI* m_rendererAPI;
		SceneData m_sceneData;
	
	public:
		void init(RendererAPI* rendererAPI) override;
		void submit(const Renderable& renderable) override;
		void setSceneData(const SceneData& sceneData) override;
		void renderSubmissions() override;
		
		bool supports(const GraphicsAPI& api) override;
		
		const std::string& getName() const override { return "SimpleRenderer"; }
	};
}
