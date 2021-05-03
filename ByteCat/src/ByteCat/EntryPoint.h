#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern ByteCat::Application* ByteCat::CreateApplication();

int main(int argc, char** argv)
{
	ByteCat::Log::Init();

	auto app = ByteCat::CreateApplication();
	app->run();
	
	delete app;
}

#endif