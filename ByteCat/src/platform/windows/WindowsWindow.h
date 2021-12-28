#pragma once
#include "byteCat/app/Window.h"
#include "byteCat/graphics/GraphicsContext.h"

namespace BC
{
	namespace Platform
	{
		class WindowsWindow : public Window
		{
		private:
			WindowSetting windowSetting;
			GraphicsContext* context;
			
			bool minimized = false;
			
		public:
			WindowsWindow(WindowSetting& setting);
			~WindowsWindow() { shutdown(); }

			// Swap the buffers, poll the events
			void update() const override;
			// Shutdown the window
			void shutdown() const override;

			// Change the window settings to the new width and heigt
			void resize(unsigned int width, unsigned int height) override;

			std::string getTitle() const override { return windowSetting.title; }
			unsigned int getWidth() const override { return windowSetting.height; }
			unsigned int getHeight() const override { return windowSetting.width; }
			
			// Change Vsync
			void setVsync(bool enabled) override;
			bool getVsync() const override { return windowSetting.vSync; }

			bool isMinimized() override { return minimized; }
			
			// Returns the native window
			void* getNativeWindow() const override;

			void setEventListener(EventListener* newListener) override;
		};
	}
}
