#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "byteCat/app/Application.h"
#include "byteCat/input/Input.h"

namespace BC
{
	namespace Input
	{
		bool IsKeyPressed(KeyCode key)
		{
			auto* window = Application::GetInstance().getWindow().getNativeWindow();
			const auto state = glfwGetKey(static_cast<GLFWwindow*>(window), static_cast<int32_t>(key));
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		bool IsMouseButtonPressed(MouseCode button)
		{
			auto* window = Application::GetInstance().getWindow().getNativeWindow();
			const auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(window), static_cast<int32_t>(button));
			return state == GLFW_PRESS;
		}

		glm::vec2 GetMousePos()
		{
			auto* window = Application::GetInstance().getWindow().getNativeWindow();
			double xpos, ypos;
			glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xpos, &ypos);

			return { (float) xpos, (float) ypos };
		}
	}
}