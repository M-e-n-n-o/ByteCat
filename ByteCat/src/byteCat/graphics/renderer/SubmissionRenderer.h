#pragma once
#include <string>
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/RendererInput.h"

namespace BC
{
	namespace Graphics
	{
		/**
		 * @brief
		 * Inherit from this class to create a custom submission Renderer. Apply this
		 * renderer in the renderer class using the SetSubmissionRenderer() method.
		 */
		class SubmissionRenderer
		{
		public:
			virtual ~SubmissionRenderer() = default;

			virtual void init(RendererAPI* rendererAPI) = 0;
			virtual void submit(const std::shared_ptr<RendererInput>& input) = 0;
			virtual void renderSubmissions() = 0;

			virtual const std::string& getName() const = 0;

			virtual bool supports(const GraphicsAPI& api) = 0;
		};
	}
}
