#pragma once

#include <glm/glm.hpp>
#include "byteCat/inputs/KeyCodes.h"
#include "byteCat/inputs/MouseCodes.h"
#include "byteCat/inputs/Gamepad.h"
#include "events/Event.h"
#include "events/KeyEvent.h"

namespace BC
{
	namespace Inputs
	{
		struct EventCallback
		{
			EventCallback(void (*callback)(const Event&)): callback(callback) {}
			virtual ~EventCallback() = default;

			void (*callback)(const Event&);
			
			virtual bool operator==(const EventCallback& other) const = 0;
			virtual bool operator==(const Event& event) const = 0;
		};

		struct KeyCallback : EventCallback
		{
			KeyCode code;

			KeyCallback(KeyCode code, void (*callback)(const Event&)): EventCallback(callback), code(code) {}
			
			bool operator==(const EventCallback& other) const override
			{
				if (const KeyCallback* otherKey = dynamic_cast<const KeyCallback*>(&other); otherKey != nullptr)
				{
					return callback == otherKey->callback && code == otherKey->code;
				}
			
				return false;
			}
			
			bool operator==(const Event& event) const override
			{
				if (event.isInCategory(EventCatKeyboard))
				{
					const KeyEvent& keyEvent = static_cast<const KeyEvent&>(event);
					
					if (keyEvent.getKeyCode() == code)
					{
						return true;
					}
				}
			
				return false;
			}
		};

		struct MouseCallback : EventCallback
		{
			EventType type;

			MouseCallback(EventType type, void (*callback)(const Event&)) : EventCallback(callback), type(type) {}

			bool operator==(const EventCallback& other) const override
			{
				if (const MouseCallback* otherMouse = dynamic_cast<const MouseCallback*>(&other); otherMouse != nullptr)
				{
					return callback == otherMouse->callback && type == otherMouse->type;
				}

				return false;
			}

			bool operator==(const Event& event) const override
			{				
				if (event.isInCategory(EventCatMouse) || event.isInCategory(EventCatMouseButton))
				{
					if (event.getEventType() == type)
					{
						return true;
					}
				}

				return false;
			}
		};
		
		class Input
		{
		private:
			inline static std::unordered_map<std::string, KeyCode> s_customKeyCodes;

			inline static std::vector<std::shared_ptr<EventCallback>> s_callbacks;
		
		public:
			// All the new events used to call callbacks with will need to be received here
			static void HandleEvent(const Event& event);

			// Call this function to add a callback to a specified key code
			static void StartListening(std::shared_ptr<EventCallback> callback);
			
			// Call this function to remove a callback from a specified key code
			static void StopListening(std::shared_ptr<EventCallback> toDelete);

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
