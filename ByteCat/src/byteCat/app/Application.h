#pragma once
#include "byteCat/app/LayerStack.h"
#include "byteCat/inputs/events/Event.h"
#include "byteCat/graphics/Window.h"
#include "byteCat/app/Layer.h"
#include "byteCat/imgui/ImGuiLayer.h"
#include "byteCat/inputs/events/ApplicationEvent.h"

namespace BC
{	
	namespace App
	{
		/**
		 * @brief
		 * This class represents the whole ByteCat application itself.
		 * When starting this class the application starts.
		 * Inherit from this class in the users application to make a ByteCat application.
		 */
		class Application : public Inputs::EventListener
		{
		private:
			static Application* s_instance;

			LayerStack m_layerStack;
			Imgui::ImGuiLayer* m_imguiLayer;

			bool m_isRunning;
		
		protected:
			Graphics::Window* m_window;

		public:
			Application();
			virtual ~Application();

			// This method gets automatically called, do not call yourself!
			void start();

			// This method calls all the things that should be called in a frame (you should probably never have to call this yourself)
			void onFrame();
			
			// This method stops the application
			void stop();
			
			// Call this function to push a new layer to the LayerStack
			void pushLayer(Layer* layer);
			// Call this function to push a new overlay to the LayerStack
			void pushOverlay(Layer* overlay);

			Graphics::Window& getWindow() const { return *m_window; }
			static Application& GetInstance() { return *s_instance; }

		protected:
			// Will be called after the start of the Application (you can have Graphics API calls from here on out)
			virtual void onApplicationStart() = 0;

		private:
			
			void onEvent(Inputs::Event& event) override;
			bool onWindowCreated(Inputs::WindowCreatedEvent& event);
			bool onWindowClose(Inputs::WindowCloseEvent& event);
			bool onWindowResize(Inputs::WindowResizeEvent& event);
			bool onWindowRender(Inputs::WindowRenderEvent& event);
		};

		// Need to be defined in the users application
		Application* CreateApplication(void* data);
	}
}
