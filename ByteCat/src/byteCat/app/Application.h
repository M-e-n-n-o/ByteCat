#pragma once
#include "byteCat/app/LayerStack.h"
#include "byteCat/input/events/Event.h"
#include "byteCat/graphics/Window.h"
#include "byteCat/app/Layer.h"
#include "byteCat/imgui/ImGuiLayer.h"
#include "byteCat/input/events/ApplicationEvent.h"

namespace BC
{
	/// <summary>
	/// This class represents the whole ByteCat application itself.
	/// When starting this class the application starts.
	///	Inherit from this class in the users application to make a ByteCat application.
	/// </summary>
	class Application : public EventListener
	{
	private:	
		static Application* s_instance;
	
		LayerStack m_layerStack;
		ImGuiLayer* m_imguiLayer;

		bool m_isRunning;

		friend int ::main(int argc, char** argv);

	protected:
		Window* m_window;
	
	public:		
		Application();
		virtual ~Application();

		// Call this function to push a new layer to the LayerStack
		void pushLayer(Layer* layer);
		// Call this function to push a new overlay to the LayerStack
		void pushOverlay(Layer* overlay);

		Window& getWindow() const { return *m_window; }
		static Application& GetInstance() { return *s_instance; }
	
	private:
		void start();

		void onEvent(Event& event) override;
		bool onWindowClose(WindowCloseEvent& event);
		bool onWindowResize(WindowResizeEvent& event);
	};

	// Need to be defined in the users application
	Application* CreateApplication();
}
