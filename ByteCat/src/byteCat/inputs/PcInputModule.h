#pragma once

#ifdef INPUT_MODULE_PC

#include <vector>
#include "byteCat/inputs/Gamepad.h"
#include "byteCat/inputs/KeyCodes.h"
#include "byteCat/inputs/MouseCodes.h"
#include "glm/vec2.hpp"

namespace BC
{
	namespace Inputs
	{
		struct CodeType
		{
			int type;
			
			union Code
			{
				KeyCode keyCode;
				MouseCode mouseCode;
				GamepadButton gamepadButton;
			} code;
		
			CodeType(const KeyCode& code) : type(0) { this->code.keyCode = code; }
			CodeType(const MouseCode& code) : type(1) { this->code.mouseCode = code; }
			CodeType(const GamepadButton& code) : type(2) { this->code.gamepadButton = code; }
		};
		
		/**
		 * @brief
		 * The input module for PC specific inputs such as mouse, keyboard and gamepad.
		 * Access this class via "Input<PcInputModule>" or "Input<>" if this is the standard input module of your application 
		 */
		class PcInputModule
		{
		private:
			inline static std::unordered_map<std::string, std::vector<CodeType>> s_customKeyCodes;
		
		public:
			virtual ~PcInputModule() = default;

			// Call this function to add a new custom key binding to the input system
			static void AddCustomKeyCode(const std::string& name, const CodeType& code);

			// Call this function to check if a specific custom key is pressed
			static bool IsPressed(const std::string& customKey);
			
			// Call this function to check if a specific key is pressed
			static bool IsPressed(const KeyCode& key);

			// Call this function to see if a specific mouse button is pressed
			static bool IsPressed(const MouseCode& button);

			// Call this function to get the current mouse position
			static glm::vec2 GetMousePos();

			// Call this function to get the mouse movement between now and the last time this function got called
			static glm::vec2 GetMouseVelocity();

			// Returns a list with all the active gamepads
			static std::vector<Gamepad> GetActiveGamepads();

			// Returns true if the given gamepad (with GamepadID) is pressing the given button
			static bool IsPressed(const GamepadButton& button, const GamepadID& id = GamepadID::ID_1);

			// Returns a value between -1 and 1 on the given axis with the given gamepad (with GamepadID)
			static float GetGamepadAxis(const GamepadAxis& axis, const GamepadID& id = GamepadID::ID_1);
		};
	}
}

#endif
