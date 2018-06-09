#include "BoolPinInput.h"
#include <Arduino.h>

BoolPinInput::BoolPinInput(pinId_t pin, bool is_low_by_default) :
	_pin(pin),
	_is_low_by_default(is_low_by_default),
	_value(0),
	_previous_value(0xFF)
{
}

void BoolPinInput::setup()
{
	pinMode(_pin, INPUT);
}

void BoolPinInput::update()
{
	_previous_value = _value;
	_value = (digitalRead(_pin) == HIGH) ^ (!_is_low_by_default);
}

bool BoolPinInput::getValue() const
{
	return _value;
}

bool BoolPinInput::hasValueChanged() const
{
	return _previous_value != _value;
}
