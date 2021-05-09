#pragma once

#include "byteCat/Core.h"
#include "byteCat/events/Event.h"
#include "byteCat/app/Window.h"

namespace BC
{
	// Inherit from this class in the users application
	class BYTECAT_API Application : public EventListener
	{
	private:
		static Application* instance;
		
		bool isRunning;
		Window* window;

		friend int ::main(int argc, char** argv);
		
	public:
		Application();
		virtual ~Application();

		Window& getWindow() const { return *window; }

		static Application& GetInstance() { return *instance; }

	private:
		void start();
		void run();
		
		virtual void update() = 0;

		void onEvent(Event& event) override;
	};

	// Need to be defined in the users application
	Application* CreateApplication();
}
