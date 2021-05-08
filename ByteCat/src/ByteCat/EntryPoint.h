#pragma once

extern BC::Application* BC::CreateApplication();

int main(int argc, char** argv)
{
	BC::Log::Init();

	auto app = BC::CreateApplication();
	app->run();
	
	delete app;
}