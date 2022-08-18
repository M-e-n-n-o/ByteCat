#pragma once
#ifdef BC_PLATFORM_PC

#include "byteCat/graphics/Window.h"
#include "byteCat/graphics/GraphicsContext.h"

namespace BC
{
	namespace Platform
	{
		class WinLinWindow : public Graphics::Window
		{
		private:
			Graphics::WindowSettings m_windowSetting;
			Graphics::GraphicsContext* m_context;
			
			bool m_isMinimized = false;
			
		public:
			WinLinWindow(const Graphics::WindowSettings& setting);
			~WinLinWindow() { shutdown(); }

			// Swap the buffers, poll the events
			void update() const override;
			// Shutdown the window
			void shutdown() const override;

			// Change the window settings to the new width and heigt
			void resize(unsigned int width, unsigned int height) override;

			std::string getTitle() const override { return m_windowSetting.title; }
			unsigned int getWidth() const override { return m_windowSetting.width; }
			unsigned int getHeight() const override { return m_windowSetting.height; }
			
			// Change Vsync
			void setVsync(bool enabled) override;
			bool getVsync() const override { return m_windowSetting.vSync; }

			bool isMinimized() override { return m_isMinimized; }

			void captureMouse(bool capture) override;
			
			// Returns the native window
			void* getNativeWindow() const override;

			void setEventListener(Inputs::EventListener* newListener) override;
		};
	}
}
#endif