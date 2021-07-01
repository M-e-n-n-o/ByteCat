#pragma once

#include "byteCat/app/Application.h"

extern BC::Application* BC::CreateApplication();

int main(int argc, char** argv)
{
	BC::Log::Init();

	auto app = BC::CreateApplication();
	app->start();
	
	delete app;
}