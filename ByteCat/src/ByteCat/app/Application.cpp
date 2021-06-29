#include "bcpch.h"
#include "byteCat/app/Application.h"

#include "byteCat/input/Input.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/render/renderers/Renderer.h"
#include "byteCat/render/models/Mesh.h"
#include "byteCat/render/models/Texture.h"
#include "byteCat/render/shaders/Shader.h"

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
    Texture2D texture("blokje.png");
	void Application::run()
	{		
        //StandardShader shader;
        //shader.init();

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
        // Texture2D texture("blokje.png");
        LOG_INFO("Texture width: {0}, height: {1}", texture.getWidth(), texture.getHeight());

        std::string vertexShader = R"(
		#version 400 core

		in vec3 position;
		in vec2 textureCoords;

		out vec2 passTextureCoords;

		
		void main(void)
		{
			gl_Position = vec4(position, 1.0);
			passTextureCoords = textureCoords;
		}
		)";

        std::string fragmentShader = R"(
		#version 400 core

		in vec2 passTextureCoords;

		out vec4 outColor;

		uniform sampler2D textureSampler;

		
		void main(void)
		{
			outColor = texture(textureSampler, passTextureCoords);
		}
		)";
		
        Shader shader(vertexShader, fragmentShader, []()
        {
			LOG_INFO("Shader textures set");
            texture.bind(1);
        });

        Renderer renderer;
		
        while (isRunning)
        {
            renderer.prepare();
            shader.bind();
            renderer.renderVAO(*mesh.vao, shader);
            shader.unbind();

            update();

            window->update();
        }
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
