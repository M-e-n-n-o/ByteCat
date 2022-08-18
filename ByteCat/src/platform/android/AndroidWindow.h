#pragma once
// #ifdef BC_PLATFORM_MOBILE

#include "byteCat/graphics/Window.h"

namespace BC
{
	namespace Platform
	{
		class AndroidWindow : public Graphics::Window
		{
		public:
			AndroidWindow(void* display);
			~AndroidWindow();
			
			void update() const override;
			
			void shutdown() const override;
			
			void resize(unsigned width, unsigned height) override;
			
			std::string getTitle() const override;
			unsigned getWidth() const override;
			unsigned getHeight() const override;
			
			void setVsync(bool enabled) override;
			bool getVsync() const override;
			
			bool isMinimized() override;
			
			void captureMouse(bool capture) override;
			
			void* getNativeWindow() const override;
			
			void setEventListener(Inputs::EventListener* newListener) override;
		};
	}
}

// #endif