#include "KeypadInput.h"
#include <Arduino.h>

KeypadInput::KeypadInput(pinId_t pin_row0, pinId_t pin_row1, pinId_t pin_row2, pinId_t pin_row3, pinId_t pin_col0, pinId_t pin_col1, pinId_t pin_col2) :
	_value(0),
	_previous_value(0),
	_keymap("123456789#0*"),
	_rowPins({pin_row0, pin_row1, pin_row2, pin_row3}),
	_colPins({pin_col0, pin_col1, pin_col2}),
	_keypad(_keymap, _rowPins, _colPins, 4, 3)
{
}

void KeypadInput::setup()
{
}

void KeypadInput::update()
{
	_previous_value = _value;
	_value = _keypad.getKey();
}

char KeypadInput::getValue() const
{
	return _value;
}

bool KeypadInput::hasValueChanged() const
{
	return _previous_value != _value;
}
