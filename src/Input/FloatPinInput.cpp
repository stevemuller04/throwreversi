#include "FloatPinInput.h"
#include <Arduino.h>

FloatPinInput::FloatPinInput(pinId_t pin, double divisor) :
	_pin(pin),
	_divisor(divisor),
	_value(0.0)
{
}

void FloatPinInput::setup()
{
	pinMode(_pin, INPUT);
}

void FloatPinInput::update()
{
	_value = analogRead(_pin) * _divisor;
}

double FloatPinInput::getValue() const
{
	return _value;
}
