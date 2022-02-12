#pragma once
#include <string>
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/RenderData.h"

namespace BC
{
	/// <summary>
	/// Inherit from this class to create a custom Renderer. Apply this
	/// renderer in the renderer class using the SetRenderer() method.
	/// </summary>
	class BaseRenderer
	{
	public:
		virtual ~BaseRenderer() = default;

		virtual void init(RendererAPI* rendererAPI) = 0;
		virtual void submit(const Renderable& renderable) = 0;
		virtual void setSceneData(const SceneData& sceneData) = 0;
		virtual void renderFrame() = 0;

		virtual const std::string& getName() const = 0;

		virtual bool supports(const GraphicsAPI& api) = 0;
	};
}
