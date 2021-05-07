#pragma once

#include "byteCat/Core.h"
#include "byteCat/events/Event.h"
#include "platform/Window.h"

namespace BC
{
	// Inherit from this class in the users application
	class BYTECAT_API Application : public EventListener
	{
	private:
		static Application* instance;
		
		bool isRunning;
		Window* window;
		
	public:
		Application();
		virtual ~Application();

		void run();

		Window& getWindow() const { return *window; }

		static Application& GetInstance() { return *instance; }

	private:
		virtual void update() = 0;
		virtual void render() = 0;

		void onEvent(Event& event) override;
	};

	// To be defined in the users application
	Application* CreateApplication();
}
