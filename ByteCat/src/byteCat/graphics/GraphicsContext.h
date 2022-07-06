#pragma once

namespace BC
{
	namespace Graphics
	{
		/**
		 * @brief
		 * This generic GraphicsContext represents the render context the renderer will render to.
		 */
		class GraphicsContext
		{
		public:
			virtual ~GraphicsContext() = default;

			virtual void init(unsigned int windowWidth, unsigned int windowHeight) = 0;
			virtual void swapBuffers() = 0;

			static GraphicsContext* Create(void* window);
		};
	}
}
