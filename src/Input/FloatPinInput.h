#ifndef INCLUDE_SRC_INPUT_FLOATPININPUT_H
#define INCLUDE_SRC_INPUT_FLOATPININPUT_H

#include "Input.h"
#include "../types.h"

/**
 * Hardware interface that provides functionality to read a numeric value from an attached device.
 */
class FloatPinInput : public Input {
	private:
		pinId_t _pin;
		double _divisor;
		double _value;

	public:
		/**
		 * Initializes a new FloatPinInput instance.
		 * @param pin - The identifier of the GPIO pin where the value shall be read from.
		 * @param divisor - A number by which the raw value read from the given pin is divided by.
		 */
		FloatPinInput(pinId_t pin, double divisor);

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
		double getValue() const;
};

#endif
