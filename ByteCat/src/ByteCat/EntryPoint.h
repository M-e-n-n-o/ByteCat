#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern ByteCat::Application* ByteCat::CreateApplication();

int main(int argc, char** argv)
{
	ByteCat::Log::Init();
	BC_CORE_INFO("Initialized Log");
	BC_INFO("Initialized Log");

	auto app = ByteCat::CreateApplication();
	BC_CORE_INFO("ByteCat engine has started");
	app->run();
	BC_CORE_INFO("Closed ByteCat engine");
	delete app;
}

#endif