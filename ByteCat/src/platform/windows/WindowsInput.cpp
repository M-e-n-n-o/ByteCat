#include "bcpch.h"

#ifdef BC_PLATFORM_WINDOWS

	#include "GLFW/glfw3.h"
	#include "byteCat/app/Application.h"
	#include "byteCat/input/Input.h"

	namespace BC
	{
		bool Input::IsKeyPressed(KeyCode key)
		{
			auto* window = Application::GetInstance().getWindow().getNativeWindow();
			const auto state = glfwGetKey(static_cast<GLFWwindow*>(window), static_cast<int32_t>(key));
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		bool Input::IsMouseButtonPressed(MouseCode button)
		{
			auto* window = Application::GetInstance().getWindow().getNativeWindow();
			const auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(window), static_cast<int32_t>(button));
			return state == GLFW_PRESS;
		}

		glm::vec2 Input::GetMousePos()
		{
			auto* window = Application::GetInstance().getWindow().getNativeWindow();
			double xpos, ypos;
			glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xpos, &ypos);
			return { (float)xpos, (float)ypos };
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

		bool Input::IsGamepadButtonPressed(GamepadButton button, GamepadID id)
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

		float Input::GetGamepadAxis(GamepadAxis axis, GamepadID id)
		{
			GLFWgamepadstate state;

			if (glfwGetGamepadState(static_cast<int>(id), &state))
			{
				return state.axes[static_cast<int>(axis)];
			}

			return 0;
		}
	}

#endif