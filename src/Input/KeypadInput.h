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
		byte const _colPins[3];
		Keypad _keypad;

	public:
		/**
		 * Initializes a new KeypadInput instance.
		 */
		KeypadInput(pinId_t pin_row0, pinId_t pin_row1, pinId_t pin_row2, pinId_t pin_row3, pinId_t pin_col0, pinId_t pin_col1, pinId_t pin_col2);

		/**
		 * @see Input::setup()
		 */
		virtual void setup() override;

		/**
		 * @see Input::update()
		 */
		virtual void update() override;

		/**
		 * Returns the value that has been read during the last call of update().
		 */
		char getValue() const;

		/**
		 * Determines if the value that has been read using update() is different from the value that has been read in the previous call of update().
		 */
		bool hasValueChanged() const;
};

#endif
