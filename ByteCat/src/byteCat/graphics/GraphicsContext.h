#pragma once

namespace BC
{
	/// <summary>
	/// This generic GraphicsContext represents the render context the renderer will render to.
	/// </summary>
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void init(unsigned int windowWidth, unsigned int windowHeight) = 0;
		virtual void swapBuffers() = 0;

		static GraphicsContext* Create(void* window);
	};
}
