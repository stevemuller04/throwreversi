#ifndef INCLUDE_SRC_INPUT_KEYPADINPUT_H
#define INCLUDE_SRC_INPUT_KEYPADINPUT_H

#include "Input.h"
#include "../types.h"
#include <Keypad.h>

/**
 * Hardware interface that provides functionality to read the pressed key of an attached key pad.
 */
class KeypadInput : public Input {
	private:
		char _value;
		char _previous_value;
		char const *_keymap;
		byte const _rowPins[4];
		byte const _colPins[4];
		Keypad _keypad;

	public:
		/**
		 * Initializes a new KeypadInput instance.
		 */
		KeypadInput(pinId_t pin_row0, pinId_t pin_row1, pinId_t pin_row2, pinId_t pin_row3, pinId_t pin_col0, pinId_t pin_col1, pinId_t pin_col2, pinId_t pin_col3);

		/**
		 * @see Input::setup()
		 */
		virtual void setup() override;

		/**
		 * @see Input::update()
		 */
		virtual void update() override;

		/**
		 * Checks if a key is being pressed.
		 */
		bool hasValue() const;

		/**
		 * Returns the key that is currently pressed.
		 */
		char getValue() const;

		/**
		 * Determines if a new key has been pressed with last invokation of update().
		 */
		bool hasNewValue() const;
};

#endif
