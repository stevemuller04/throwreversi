#include "BoolPinOutput.h"
#include <Arduino.h>

BoolPinOutput::BoolPinOutput(pinId_t pin, bool true_induces_high) :
	_pin(pin),
	_true_induces_high(true_induces_high),
	_value(false)
{
}

void BoolPinOutput::setup()
{
	pinMode(_pin, OUTPUT);
}

void BoolPinOutput::flush()
{
	if (_value_has_changed)
	{
		digitalWrite(_pin, _value ^ (!_true_induces_high) ? HIGH : LOW);
		_value_has_changed = false;
	}
}

void BoolPinOutput::setValue(bool value)
{
	if (_value != value)
	{
		_value = value;
		_value_has_changed = true;
	}
}
