#include "KeypadInput.h"
#include <Arduino.h>

KeypadInput::KeypadInput() :
	_value(0),
	_previous_value(0)
{
	// TODO
}

void KeypadInput::setup()
{
	// TODO
}

void KeypadInput::update()
{
	_previous_value = _value;
	_value = 0; // TODO
}

char KeypadInput::getValue() const
{
	return _value;
}

bool KeypadInput::hasValueChanged() const
{
	return _previous_value != _value;
}
