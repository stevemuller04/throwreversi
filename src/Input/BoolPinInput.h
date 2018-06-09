#ifndef INCLUDE_SRC_INPUT_BOOLPININPUT_H
#define INCLUDE_SRC_INPUT_BOOLPININPUT_H

#include "Input.h"
#include "../types.h"
#include <Arduino.h>

/**
 * Hardware interface that provides functionality to read a boolean value from an attached device.
 */
class BoolPinInput : public Input {
	private:
		pinId_t _pin;
		bool _is_low_by_default;
		uint8_t _value;
		uint8_t _previous_value;

	public:
		/**
		 * Initializes a new BoolPinInput instance.
		 * @param pin - The identifier of the GPIO pin where the value shall be read from.
		 * @param is_low_by_default - If true, then the "LOW" pin state is interpreted as "false"; otherwise, "HIGH" is interpreted as "false".
		 */
		BoolPinInput(pinId_t pin, bool is_low_by_default);

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
		bool getValue() const;

		/**
		 * Determines if the value that has been read using update() is different from the value that has been read in the previous call of update().
		 */
		bool hasValueChanged() const;
};

#endif
