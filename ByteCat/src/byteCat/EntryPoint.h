#pragma once

#include "byteCat/app/Application.h"

// This is defined on the users side
extern BC::App::Application* CreateApplication();

// The start of the whole application
int main(int argc, char** argv)
{
	BC::Log::Init();

	auto app = BC::App::CreateApplication();
	app->start();

	delete app;
}