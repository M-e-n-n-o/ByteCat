#pragma once

#include "Core.h"

namespace ByteCat
{
	class BYTECAT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in client
	Application* createApplication();
}