#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern ByteCat::Application* ByteCat::CreateApplication();

int main(int argc, char** argv)
{
	ByteCat::Log::Init();

	auto app = ByteCat::CreateApplication();
	BC_CORE_INFO("ByteCat engine has started");
	app->run();
	BC_CORE_INFO("ByteCat engine has closed");

	delete app;
}

#endif