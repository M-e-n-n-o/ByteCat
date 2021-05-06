#pragma once

#include <GLFW/glfw3.h>
#include "byteCat/platform/Window.h"

namespace BC
{
	class WindowsWindow : public Window
	{
	private:
		GLFWwindow* window;
		
	public:
		WindowsWindow(WindowSetting& windowSetting);
		~WindowsWindow() override { shutdown(); };
		
		void update() override;
		void shutdown() override;
		
		void setVsync(bool enabled) override;
		
		void* getWindow() const override { return window; };
	};
}
