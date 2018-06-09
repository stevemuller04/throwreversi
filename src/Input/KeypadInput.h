#ifndef INCLUDE_SRC_INPUT_KEYPADINPUT_H
#define INCLUDE_SRC_INPUT_KEYPADINPUT_H

#include "Input.h"
#include "../types.h"

/**
 * Hardware interface that provides functionality to read the pressed key of an attached key pad.
 */
class KeypadInput : public Input {
	private:
		char _value;
		char _previous_value;

	public:
		/**
		 * Initializes a new KeypadInput instance.
		 */
		KeypadInput();

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
