#pragma once

#include "byteCat/events/Event.h"
#include "byteCat/input/KeyCodes.h"

namespace BC
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
		EventType getEventType() const override { return EventType::KeyPressed; }
	};


	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}
		
		EventType getEventType() const override { return EventType::KeyReleased; }
	};

	
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}
		
		EventType getEventType() const override { return EventType::KeyTyped; }
	};
}
