#pragma once
#include "byteCat/graphics/Window.h"
#include "byteCat/graphics/GraphicsContext.h"

namespace BC
{
	namespace Platform
	{
		class WinLinWindow : public Window
		{
		private:
			WindowSettings m_windowSetting;
			GraphicsContext* m_context;
			
			bool m_isMinimized = false;
			
		public:
			WinLinWindow(WindowSettings& setting);
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
			
			// Returns the native window
			void* getNativeWindow() const override;

			void setEventListener(EventListener* newListener) override;
		};
	}
}
