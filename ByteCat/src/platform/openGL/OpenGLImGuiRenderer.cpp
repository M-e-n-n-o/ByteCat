#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
#include "bcpch.h"
#include "platform/openGL/OpenGLImGuiRenderer.h"
#include "byteCat/app/Application.h"

#if defined(BC_PLATFORM_PC)
	#include <GLFW/glfw3.h>
	#include "imgui_impl_glfw.h"
	#include "imgui_impl_opengl3.h"
#endif

namespace BC
{
	namespace Platform
	{
		void OpenGLImGuiRenderer::enable()
		{
#if defined(BC_PLATFORM_PC)
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;		// Enable Keyboard controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;		// Enable Gamepad controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
			
			ImGui::StyleColorsDark();

			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			GLFWwindow* window = static_cast<GLFWwindow*>(App::Application::GetInstance().getWindow().getNativeWindow());

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 450");
#elif defined(BC_PLATFORM_MOBILE)
			LOG_INFO("ImGui is disabled for now on Mobile");
#endif
		}

		void OpenGLImGuiRenderer::disable()
		{
#if defined(BC_PLATFORM_PC)
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
#endif
		}

		void OpenGLImGuiRenderer::begin()
		{
#if defined(BC_PLATFORM_PC)
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
#endif
		}

		void OpenGLImGuiRenderer::end()
		{
#if defined(BC_PLATFORM_PC)
			ImGuiIO& io = ImGui::GetIO();
			auto& window = App::Application::GetInstance().getWindow();
			io.DisplaySize = ImVec2(window.getWidth(), window.getHeight());

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
#endif
		}
	}
}
#endif