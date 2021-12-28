#pragma once

#include "byteCat/app/LayerStack.h"
#include "byteCat/input/events/Event.h"
#include "byteCat/app/Window.h"
#include "byteCat/app/Layer.h"
#include "byteCat/input/events/ApplicationEvent.h"

namespace BC
{
	/// <summary>
	/// This class represents the whole ByteCat application itself.
	/// When starting this class the application starts.
	/// Inherit from this class in the users application to make a ByteCat application.
	/// </summary>
	class Application : public EventListener
	{
	private:
		static Application* instance;
		
		LayerStack layerStack;

		Window* window;
		bool isRunning;

		friend int ::main(int argc, char** argv);
		
	public:
		Application();
		virtual ~Application();

		// Call this function to push a new layer to the LayerStack
		void pushLayer(Layer* layer);
		// Call this function to push a new overlay to the LayerStack
		void pushOverlay(Layer* overlay);

		Window& getWindow() const { return *window; }
		static Application& GetInstance() { return *instance; }
	
	private:
		void start();
		void run();

		void onEvent(Event& event) override;
		bool onWindowClose(WindowCloseEvent& event);
		bool onWindowResize(WindowResizeEvent& event);
	};

	// Need to be defined in the users application
	Application* CreateApplication();
}
