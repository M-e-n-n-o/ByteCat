#pragma once

	#include "byteCat/app/Application.h"

	// This is defined on the users side
	extern BC::App::Application* CreateApplication(void* data);

#ifdef BC_PLATFORM_PC
	int main(int argc, char** argv)
#elif defined(BC_PLATFORM_MOBILE)
	#include <glfm.h>

	void glfmMain(GLFMDisplay* display)
#endif
	{
  		BC::Log::Init();
		
#ifdef BC_PLATFORM_PC
		auto app = BC::App::CreateApplication(argv[0]);
#elif defined(BC_PLATFORM_MOBILE)
		auto app = BC::App::CreateApplication(display);
#endif
		
#ifdef BC_PLATFORM_PC
  		app->start();

  		delete app;
#endif
	}