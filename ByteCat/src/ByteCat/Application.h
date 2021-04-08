#pragma once

#include "Core.h"

namespace ByteCat
{
	// Inherit from this class in the users application
	class BYTECAT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in the users application
	Application* CreateApplication();
}