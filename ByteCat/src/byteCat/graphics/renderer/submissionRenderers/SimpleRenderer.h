#pragma once
#include <memory>
#include "byteCat/graphics/renderer/SubmissionRenderer.h"

namespace BC
{
	namespace Graphics
	{
		class SimpleRenderer : public SubmissionRenderer
		{
		private:
			RendererAPI* m_rendererAPI;

			std::vector<std::shared_ptr<Renderable>> m_entities;
			std::shared_ptr <CameraData> m_cameraData;

		public:
			void init(RendererAPI* rendererAPI) override;
			void submit(const std::shared_ptr<RendererInput>& input) override;
			void renderSubmissions() override;

			bool supports(const GraphicsAPI& api) override;

			const std::string& getName() const override { return "SimpleRenderer"; }
		};
	}
}
