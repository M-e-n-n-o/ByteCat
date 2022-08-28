#pragma once
#ifdef BC_PLATFORM_MOBILE

#include "byteCat/graphics/Window.h"

namespace BC
{
	namespace Platform
	{
		class MobileWindow : public Graphics::Window
		{
		private:
			
		public:
			MobileWindow(Graphics::WindowSettings settings, void* appInputData);
			~MobileWindow();
			
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

#endif