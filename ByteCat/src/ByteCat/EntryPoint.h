#pragma once

#include "byteCat/app/Application.h"

// This is defined on the users side
extern BC::Application* BC::CreateApplication();

// The start of the whole application
int main(int argc, char** argv)
{
	BC::Log::Init();

	auto app = BC::CreateApplication();
	app->start();
	
	delete app;
}