#include "bcpch.h"
#include "byteCat/app/Application.h"

#include "byteCat/input/Input.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/render/Renderer.h"
#include "byteCat/render/models/Mesh.h"
#include "byteCat/render/models/Texture.h"
#include "byteCat/render/shaders/Shader.h"
#include "byteCat/render/shaders/StandardShader.h"
#include "byteCat/utils/Maths.h"

namespace BC
{	
    Application* Application::instance = nullptr;
	
	Application::Application() : isRunning(false)
	{
        LOG_ASSERT(!instance, "Application already exists!");
        instance = this;
		
        LOG_INFO("ByteCat engine is starting...");
		
        WindowSetting setting = { "ByteCat Engine", 1280, 720, true };
        window = new Window(setting);
        window->setEventListener(this);
	}

    Application::~Application()
    {
        LOG_INFO("ByteCat engine is closing...");

        delete window;
    }

    void Application::start()
    {
        if (isRunning)
        {
            LOG_WARN("Cannot run the main game loop synchronous");
            return;
        }
        isRunning = true;

        run();
    }
	
	void Application::run()
	{	
   //      std::vector<float> vertices =
   //      {
		 //  -0.5f, 0.5f, 0,
		 //  -0.5f, -0.5f, 0,
		 //  0.5f, -0.5f, 0,
		 //  0.5f, 0.5f, 0
   //      };
   //
   //      std::vector<int> indices =
   //      {
   //          0,1,3,
			// 3,1,2
   //      };
   //
   //      std::vector<float> textureCoords =
   //      {
   //      	0, 0,
   //      	0, 1,
   //      	1, 1,
   //      	1, 0
   //      };
   //
   //      Mesh mesh(vertices, textureCoords, indices);
   //      Texture2D texture("blokje.png");
		 //
   //      StandardShader shader(texture);
         Renderer renderer;
   //
   //      while (isRunning)
   //      {        	
   //          renderer.prepare();
   //          shader.bind();
   //          shader.loadMatrix4("modelMatrix", Utils::CreateModelMatrix(glm::vec3(-1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
   //          renderer.renderVAO(*mesh.vao, shader);
   //          shader.unbind();
   //
   //          update();
   //
   //          window->update();
   //      }

		while (isRunning)
		{
            renderer.prepare();

			for (Layer* layer : layerStack)
			{
                layer->onUpdate();
			}

            window->update();
		}
	}

    void Application::onEvent(Event& event)
    {
		if (event.getEventType() == EventType::WindowClose)
		{
            isRunning = false;
            event.handled = true;
		}
		
        for (auto it = layerStack.end(); it != layerStack.begin();)
        {
            (*--it)->onEvent(event);
        	if (event.handled)
        	{
        		break;
        	}
        }
    }

    void Application::pushLayer(Layer* layer)
    {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* overlay)
    {
        layerStack.pushLayer(overlay);
        overlay->onAttach();
    }
}
