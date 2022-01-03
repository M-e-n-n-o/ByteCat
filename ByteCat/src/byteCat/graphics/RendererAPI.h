#pragma once

namespace BC
{
	enum class GraphicsAPI
	{
		None = 0,
		OpenGL = 1
	};

	class RendererAPI
	{
	private:
		static GraphicsAPI graphicsAPI;
	
	public:
		static void SetGraphicsAPI(GraphicsAPI api);
		static GraphicsAPI& GetAPI() { return graphicsAPI; }
	};
}