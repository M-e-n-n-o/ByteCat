#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "byteCat/Application.h"
#include "byteCat/input/Input.h"

#ifdef BC_PLATFORM_WINDOWS

namespace BC
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
		const auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}
	
	glm::vec2 Input::getMousePos()
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float) xpos, (float) ypos };
	}
}

#endif