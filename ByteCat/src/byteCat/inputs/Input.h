#pragma once

#include <glm/glm.hpp>

#include "byteCat/inputs/EventCallback.h"
#include "byteCat/inputs/KeyCodes.h"
#include "byteCat/inputs/MouseCodes.h"
#include "byteCat/inputs/Gamepad.h"
#include "byteCat/inputs/events/Event.h"

namespace BC
{
	namespace Inputs
	{		
		class Input
		{
		private:
			inline static std::unordered_map<std::string, KeyCode> s_customKeyCodes;

			inline static std::vector<std::shared_ptr<EventCallback>> s_callbacks;
		
		public:
			// All the new events used to call callbacks with will need to be received here
			static void HandleEvent(const Event& event);

			// Call this function to add a callback to a specified key code, returns the id of the callback
			static int StartListening(const std::shared_ptr<EventCallback>& callback);
			
			// Call this function to remove a callback
			static void StopListening(int& id);

			// Call this function to add a new custom key binding to the input system
			static void AddCustomKeyCode(const std::string& name, const KeyCode& code);
			
			// Call this function to check if a specific key is pressed
			static bool IsKeyPressed(KeyCode key);
			
			// Call this function to check if a specific custom key is pressed
			static bool IsKeyPressed(const std::string& customKey);

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
