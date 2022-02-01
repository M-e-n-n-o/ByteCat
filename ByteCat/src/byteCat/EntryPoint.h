#pragma once

#include "byteCat/app/Application.h"

// This is defined on the users side
extern BC::Application* BC::CreateApplication();

// The start of the whole application
int main(int argc, char** argv)
{
	BC::Log::Init();

#if defined(BC_DEBUG)
	LOG_INFO("DEBUG BUILD");
#elif defined(BC_RELEASE)
	LOG_INFO("RELEASE BUILD");
#elif defined(BC_DIST)
	LOG_INFO("DISTRIBUTION BUILD");
#endif
	
	auto app = BC::CreateApplication();
	app->start();
	
	delete app;
}