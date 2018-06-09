#ifndef INCLUDE_SRC_INPUT_RGBWLEDOUTPUT_H
#define INCLUDE_SRC_INPUT_RGBWLEDOUTPUT_H

#include "RgbwLedStripOutput.h"
#include "../types.h"
#include "../rgbw.h"
#include <Adafruit_NeoPixel.h>

/**
 * Hardware interface that provides functionality to control a single RGBW "NeoPixel" LED.
 */
class RgbwLedOutput : public RgbwLedStripOutput {
	public:
		/**
		 * Initializes a new RgbwLedStripOutput.
		 * @param pin - The identifier of the GPIO pin which the LED (more precisely: its DATA pin) is connected to.
		 * @param pixel_type_flags - Additional flags describing the nature of the LED. These flags are passed to the internal Adafruit_NeoPixel instance.
		 */
		RgbwLedOutput(pinId_t pin, neoPixelType pixel_type_flags);

		/**
		 * Sets the color of a specified LED in the internal buffer.
		 * Commit the changes on the LED strip using flush().
		 * @param index - The zero-based index of the LED on the LED strip.
		 * @param color - The color that shall be displayed on the LED.
		 */
		void setColor(rgbw const &color);
};

#endif
