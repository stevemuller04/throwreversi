#ifndef INCLUDE_SRC_INPUT_RGBWLEDSTRIPOUTPUT_H
#define INCLUDE_SRC_INPUT_RGBWLEDSTRIPOUTPUT_H

#include "Output.h"
#include "../types.h"
#include "../rgbw.h"
#include <Adafruit_NeoPixel.h>

/**
 * Hardware interface that provides functionality to control an LED strip consisting of RGBW "NeoPixel" LEDs.
 */
class RgbwLedStripOutput : public Output {
	private:
		Adafruit_NeoPixel _led;
		bool _need_flush = false;

	public:
		/**
		 * Initializes a new RgbwLedStripOutput.
		 * @param num_leds - The number of LEDs which the LED strip consists of.
		 * @param pin - The identifier of the GPIO pin which the LED strip (more precisely: its DATA pin) is connected to.
		 * @param pixel_type_flags - Additional flags describing the nature of the LEDs. These flags are passed to the internal Adafruit_NeoPixel instance.
		 */
		RgbwLedStripOutput(ledId_t num_leds, pinId_t pin, neoPixelType pixel_type_flags);

		/**
		 * @see Input::setup()
		 */
		virtual void setup() override;

		/**
		 * @see Output::flush()
		 */
		virtual void flush() override;

		/**
		 * Sets the color of a specified LED in the internal buffer.
		 * Commit the changes on the LED strip using flush().
		 * @param index - The zero-based index of the LED on the LED strip.
		 * @param color - The color that shall be displayed on the LED.
		 */
		void setColor(ledId_t index, rgbw const &color);
};

#endif
