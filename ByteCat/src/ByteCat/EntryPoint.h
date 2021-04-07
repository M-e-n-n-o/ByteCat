#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern ByteCat::Application* ByteCat::createApplication();

int main(int argc, char** argv)
{
	ByteCat::Log::init();
	BC_CORE_INFO("Initialized Log");
	BC_INFO("Initialized Log");

	auto app = ByteCat::createApplication();
	app->run();
	delete app;
}

#endif