#include "bcpch.h"

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)

	#include "GLFW/glfw3.h"
	#include "byteCat/app/Application.h"
	#include "byteCat/inputs/Input.h"

namespace BC
{
	namespace Inputs
	{
		bool Input::IsPressed(const KeyCode& key)
		{
			auto* window = App::Application::GetInstance().getWindow().getNativeWindow();
			const auto state = glfwGetKey(static_cast<GLFWwindow*>(window), static_cast<int32_t>(key));
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		bool Input::IsPressed(const MouseCode& button)
		{
			auto* window = App::Application::GetInstance().getWindow().getNativeWindow();
			const auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(window), static_cast<int32_t>(button));
			return state == GLFW_PRESS;
		}

		glm::vec2 Input::GetMousePos()
		{
			auto* window = App::Application::GetInstance().getWindow().getNativeWindow();
			double xpos, ypos;
			glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xpos, &ypos);
			return { (float)xpos, (float)ypos };
		}

		glm::vec2 Input::GetMouseVelocity()
		{
			static glm::vec2 previous = glm::vec2(0, 0);

			const glm::vec2 current = GetMousePos();
			const glm::vec2 velocity = current - previous;

			previous = current;

			return velocity;
		}

		std::vector<Gamepad> Input::GetActiveGamepads()
		{
			std::vector<Gamepad> gamepads;

			for (int i = 0; i < 16; i++)
			{
				if (glfwJoystickIsGamepad(i))
				{
					const char* name = glfwGetGamepadName(i);
					gamepads.push_back({ static_cast<GamepadID>(i), name });
				}
			}

			return gamepads;
		}

		bool Input::IsPressed(const GamepadButton& button, const GamepadID& id)
		{
			GLFWgamepadstate state;

			if (glfwGetGamepadState(static_cast<int>(id), &state))
			{
				if (state.buttons[static_cast<int>(button)])
				{
					return true;
				}
			}

			return false;
		}

		float Input::GetGamepadAxis(const GamepadAxis& axis, const GamepadID& id)
		{
			GLFWgamepadstate state;

			if (glfwGetGamepadState(static_cast<int>(id), &state))
			{
				return state.axes[static_cast<int>(axis)];
			}

			return 0;
		}
	}
}

#endif
