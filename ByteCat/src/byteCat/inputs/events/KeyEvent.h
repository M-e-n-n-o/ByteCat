#pragma once

#include "byteCat/inputs/events/Event.h"
#include "byteCat/inputs/KeyCodes.h"

namespace BC
{
	namespace Inputs
	{
		class KeyEvent : public Event
		{
		private:
			KeyCode keyCode;

		protected:
			KeyEvent(const KeyCode keyCode) : keyCode(keyCode) {}

		public:
			KeyCode getKeyCode() const { return keyCode; }
			int getCategoryFlags() const override { return EventCatInput | EventCatKeyboard; }
		};


		class KeyPressedEvent : public KeyEvent
		{
		private:
			bool isRepeat;

		public:
			KeyPressedEvent(const KeyCode keyCode, bool isRepeat) : KeyEvent(keyCode), isRepeat(isRepeat) {}

			bool isRepeatEvent() const { return isRepeat; }

			EVENT_CLASS_TYPE(KeyPressed)
		};


		class KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

			EVENT_CLASS_TYPE(KeyReleased)
		};


		class KeyTypedEvent : public KeyEvent
		{
		public:
			KeyTypedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

			EVENT_CLASS_TYPE(KeyTyped)
		};
	}
}
