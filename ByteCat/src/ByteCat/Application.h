#pragma once

#include "Core.h"

namespace BC
{
	// Inherit from this class in the users application
	class BYTECAT_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void update() = 0;
		virtual void render() = 0;

		void run();
	};

	// To be defined in the users application
	Application* CreateApplication();
}