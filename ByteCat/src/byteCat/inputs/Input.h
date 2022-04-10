#pragma once

#include <glm/glm.hpp>
#include "byteCat/inputs/KeyCodes.h"
#include "byteCat/inputs/MouseCodes.h"
#include "byteCat/inputs/Gamepad.h"

namespace BC
{
	namespace Inputs
	{
		class Input
		{
		public:
			// Call this function to check if a specific key is pressed
			static bool IsKeyPressed(KeyCode key);

			// Call this function to see if a specific mouse button is pressed
			static bool IsMouseButtonPressed(MouseCode button);

			// Call this function to get the current mouse position
			static glm::vec2 GetMousePos();

			// Call this function to get the mouse movement between now and the last time this function got called
			static glm::vec2 GetMouseVelocity();

			// Returns a list with all the active gamepads
			static std::vector<Gamepad> GetActiveGamepads();

			// Returns true if the given gamepad (with GamepadID) is pressing the given button
			static bool IsGamepadButtonPressed(GamepadButton button, GamepadID id = GamepadID::ID_1);

			// Returns a value between -1 and 1 on the given axis with the given gamepad (with GamepadID)
			static float GetGamepadAxis(GamepadAxis axis, GamepadID id = GamepadID::ID_1);
		};
	}
}
