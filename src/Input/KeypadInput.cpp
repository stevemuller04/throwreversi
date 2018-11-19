#include "KeypadInput.h"
#include <Arduino.h>

KeypadInput::KeypadInput(pinId_t pin_row0, pinId_t pin_row1, pinId_t pin_row2, pinId_t pin_row3, pinId_t pin_col0, pinId_t pin_col1, pinId_t pin_col2, pinId_t pin_col3) :
	_value(NO_KEY),
	_previous_value(NO_KEY),
	_keymap("123A456B789C*0#D"),
	_rowPins({pin_row0, pin_row1, pin_row2, pin_row3}),
	_colPins({pin_col0, pin_col1, pin_col2, pin_col3}),
	_keypad(_keymap, _rowPins, _colPins, 4, 4)
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

bool KeypadInput::hasValue() const
{
	return _value != NO_KEY;
}

char KeypadInput::getValue() const
{
	return _value;
}

bool KeypadInput::hasNewValue() const
{
	return hasValue() && _value != _previous_value;
}
