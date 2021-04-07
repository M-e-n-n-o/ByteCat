#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern ByteCat::Application* ByteCat::createApplication();

int main(int argc, char** argv)
{
	std::cout << "Starting the ByteCat Engine... :D";
	auto app = ByteCat::createApplication();
	app->run();
	delete app;
}

#endif