#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern BC::Application* BC::CreateApplication();

int main(int argc, char** argv)
{
	BC::CORE::Log::Init();

	auto app = BC::CreateApplication();
	app->run();
	
	delete app;
}

#endif