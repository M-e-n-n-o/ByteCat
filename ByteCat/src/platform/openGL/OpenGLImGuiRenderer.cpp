#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "platform/openGL/OpenGLImGuiRenderer.h"
#include "byteCat/app/Application.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace BC
{
	namespace Platform
	{
		void OpenGLImGuiRenderer::enable()
		{
			// IMGUI_CHECKVERSION();
			// ImGui::CreateContext();
			// ImGuiIO& io = ImGui::GetIO();
			// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;		// Enable Keyboard controls
			// // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;		// Enable Gamepad controls
			// // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			// // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
			// // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
			// // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

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
		}

		void OpenGLImGuiRenderer::disable()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		void OpenGLImGuiRenderer::begin()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void OpenGLImGuiRenderer::end()
		{
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
		}
	}
}
