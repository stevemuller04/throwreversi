#ifndef INCLUDE_SRC_INPUT_BOOLPINOUTPUT_H
#define INCLUDE_SRC_INPUT_BOOLPINOUTPUT_H

#include "Output.h"
#include "../types.h"

/**
 * Hardware interface that provides functionality to turn on or off a certain feature of an attached device.
 */
class BoolPinOutput : public Output {
	private:
		pinId_t _pin;
		bool _true_induces_high;
		bool _value;
		bool _value_has_changed = false;

	public:
		/**
		 * Initializes a new BoolPinOutput instance.
		 * @param pin - The identifier of the GPIO pin where the attached device can be controlled.
		 * @param true_induces_high - If true, then a digital "HIGH" will be written to the given pin whenever the interface value is "true"; otherwise "LOW" will be written.
		 */
		BoolPinOutput(pinId_t pin, bool true_induces_high);

		/**
		 * @see Input::setup()
		 */
		virtual void setup() override;

		/**
		 * @see Output::flush()
		 */
		virtual void flush() override;

		/**
		 * Sets the buffered value of this hardware interface to the given value.
		 * Send the value to the device using flush().
		 * @param value - The boolean value. Depending on the value of "true_induces_high" (see constructor), this translates to "HIGH" or "LOW" for the attached device.
		 */
		void setValue(bool value);
};

#endif
