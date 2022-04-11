#pragma once
#include "byteCat/Core.h"
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
		/// <summary>
		/// This class represents the whole ByteCat application itself.
		/// When starting this class the application starts.
		///	Inherit from this class in the users application to make a ByteCat application.
		/// </summary>
		class Application : public Inputs::EventListener
		{
		private:
			static Application* s_instance;

			LayerStack m_layerStack;
			Imgui::ImGuiLayer* m_imguiLayer;

			bool m_isRunning;

			friend int ::main(int argc, char** argv);

		protected:
			Graphics::Window* m_window;

		public:
			Application();
			virtual ~Application();
			
			// Call this function to push a new layer to the LayerStack
			void pushLayer(Layer* layer);
			// Call this function to push a new overlay to the LayerStack
			void pushOverlay(Layer* overlay);

			Graphics::Window& getWindow() const { return *m_window; }
			static Application& GetInstance() { return *s_instance; }

		private:
			void start();
			
			void onEvent(Inputs::Event& event) override;
			bool onWindowClose(Inputs::WindowCloseEvent& event);
			bool onWindowResize(Inputs::WindowResizeEvent& event);
		};

		// Need to be defined in the users application
		Application* CreateApplication();
	}
}
