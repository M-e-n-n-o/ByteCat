#pragma once

#include "byteCat/app/LayerStack.h"
#include "byteCat/Core.h"
#include "byteCat/input/events/Event.h"
#include "byteCat/app/Window.h"
#include "byteCat/app/Layer.h"
#include "byteCat/imgui/ImGuiLayer.h"
#include "byteCat/input/events/ApplicationEvent.h"

namespace BC
{
	// Inherit from this class in the users application
	class Application : public EventListener
	{
	private:
		static Application* instance;

		LayerStack layerStack;
		ImGuiLayer* imGuiLayer;
		
		bool isRunning;
		bool isMinimized;
		Window* window;

		friend int ::main(int argc, char** argv);
		
	public:
		Application();
		virtual ~Application();

		void pushLayer(Layer* layer);
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
