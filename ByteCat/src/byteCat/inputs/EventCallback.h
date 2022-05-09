#pragma once
#include "byteCat/inputs/EventCallback.h"
#include "byteCat/inputs/KeyCodes.h"
#include "byteCat/inputs/events/Event.h"
#include "byteCat/inputs/events/KeyEvent.h"

namespace BC
{
	namespace Inputs
	{
		struct EventCallback
		{
			EventCallback(void (*callback)(const Event&)) : callback(callback) {}
			virtual ~EventCallback() = default;

			void (*callback)(const Event&);
			
			virtual bool operator==(const Event& event) const = 0;
		};

		struct KeyCallback : EventCallback
		{
			KeyCode code;

			KeyCallback(KeyCode code, void (*callback)(const Event&)) : EventCallback(callback), code(code) {}
			
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
	}
}
