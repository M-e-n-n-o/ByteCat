#include "bcpch.h"

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
#ifdef INPUT_MODULE_PC

#include "GLFW/glfw3.h"
#include "byteCat/app/Application.h"
#include "byteCat/inputs/PcInputModule.h"

namespace BC
{
	namespace Inputs
	{
		void PcInputModule::AddCustomKeyCode(const std::string& name, const CodeType& code)
		{
			s_customKeyCodes.insert({ name, std::vector<CodeType>() });
			s_customKeyCodes[name].push_back(code);
		}

		bool PcInputModule::IsPressed(const std::string& customKey)
		{
			const auto value = s_customKeyCodes.find(customKey);
			
			if (value == s_customKeyCodes.end())
			{
				LOG_ERROR("Custom key: {0} does not exist", customKey);
				return false;
			}
		
			for (const auto& code : value->second)
			{
				bool isActive = false;
				switch (code.type)
				{
				case 0:		isActive = IsPressed(code.code.keyCode); break;
				case 1:		isActive = IsPressed(code.code.mouseCode); break;
				case 2:		isActive = IsPressed(code.code.gamepadButton); break;
				default:	LOG_WARN("CodeType was not detected!"); break;
				}
				
				if (isActive)
				{
					return true;
				}
			}
			
			return false;
		}

		bool PcInputModule::IsPressed(const KeyCode& key)
		{
			auto* window = App::Application::GetInstance().getWindow().getNativeWindow();
			const auto state = glfwGetKey(static_cast<GLFWwindow*>(window), static_cast<int32_t>(key));
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		bool PcInputModule::IsPressed(const MouseCode& button)
		{
			auto* window = App::Application::GetInstance().getWindow().getNativeWindow();
			const auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(window), static_cast<int32_t>(button));
			return state == GLFW_PRESS;
		}

		glm::vec2 PcInputModule::GetMousePos()
		{
			auto* window = App::Application::GetInstance().getWindow().getNativeWindow();
			double xpos, ypos;
			glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xpos, &ypos);
			return { (float)xpos, (float)ypos };
		}

		glm::vec2 PcInputModule::GetMouseVelocity()
		{
			static glm::vec2 previous = glm::vec2(0, 0);
		
			const glm::vec2 current = GetMousePos();
			const glm::vec2 velocity = current - previous;
		
			previous = current;
		
			return velocity;
		}

		std::vector<Gamepad> PcInputModule::GetActiveGamepads()
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

		bool PcInputModule::IsPressed(const GamepadButton& button, const GamepadID& id)
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

		float PcInputModule::GetGamepadAxis(const GamepadAxis& axis, const GamepadID& id)
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
#endif
