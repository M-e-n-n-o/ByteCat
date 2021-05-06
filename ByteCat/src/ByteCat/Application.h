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
		static Scope<Window> window;
		
	public:
		Application();
		virtual ~Application();

		virtual void update() = 0;
		virtual void render() = 0;

		void run();

		static Window& GetWindow() { return *window; };
		
		void onEvent(Event& event) override;
	};

	// To be defined in the users application
	Application* CreateApplication();
}
