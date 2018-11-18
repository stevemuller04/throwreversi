#include "BoolPinInput.h"
#include <Arduino.h>

BoolPinInput::BoolPinInput(pinId_t pin, bool is_low_by_default) :
	_pin(pin),
	_is_low_by_default(is_low_by_default),
	_pressed(false),
	_previously_pressed(false),
	_state(false)
{
}

void BoolPinInput::setup()
{
	pinMode(_pin, INPUT);
}

void BoolPinInput::update()
{
	_previously_pressed = _pressed;
	_pressed = (digitalRead(_pin) == HIGH) ^ (!_is_low_by_default);

	if (_pressed && !_previously_pressed)
	{
		_state = !_state;
	}
}

bool BoolPinInput::getValue() const
{
	return _state;
}

bool BoolPinInput::hasValueChanged() const
{
	return _pressed && !_previously_pressed;
}
