#include "bcpch.h"
#include "byteCat/app/Application.h"

#include "byteCat/input/Input.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/render/renderers/MeshRenderer.h"
#include "byteCat/render/shaders/StandardShader.h"
#include "byteCat/render/models/Mesh.h"
#include "byteCat/render/models/Texture.h"

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
        StandardShader shader;
        shader.init();

        //MeshRenderer renderer;
		
        std::vector<float> vertices =
        {
		  -0.5f, 0.5f, 0,
		  -0.5f, -0.5f, 0,
		  0.5f, -0.5f, 0,
		  0.5f, 0.5f, 0
        };

        std::vector<int> indices =
        {
            0,1,3,
			3,1,2
        };

        std::vector<float> textureCoords =
        {
        	0, 0,
        	0, 1,
        	1, 1,
        	1, 0
        };

        Mesh mesh(vertices, textureCoords, indices);
        Texture2D texture("blokje.png");
        LOG_INFO("Texture width: {0}, height: {1}", texture.getWidth(), texture.getHeight());
		
		// while (isRunning)
  //       {
  //           renderer.prepare();
  //           shader.bind();
  //           renderer.render(texturedModel);
  //           shader.unbind();
		// 	
  //           // Update
  //           update();
  //
  //           window->update();
  //       }
	}

    void Application::onEvent(Event& event)
    {		
        switch (event.getEventType())
        {
		case EventType::WindowClose:
	        {
				isRunning = false;
                event.handled = true;
                break;
	        }
        }
    }

	Application::~Application()
    {
        LOG_INFO("ByteCat engine is closing...");
		
        delete window;
    }
}
