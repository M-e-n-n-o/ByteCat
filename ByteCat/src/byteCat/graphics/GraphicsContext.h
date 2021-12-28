#pragma once

namespace BC
{
	/* Class GraphicsContext
	 *
	 * @desc
	 *	This generic GraphicsContext represents the render context the renderer will render to.
	 */
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void init() = 0;
		virtual void swapBuffers() = 0;

		static GraphicsContext* Create(void* window);
	};
}
