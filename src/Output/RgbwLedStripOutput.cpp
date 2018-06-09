#include "RgbwLedStripOutput.h"

RgbwLedStripOutput::RgbwLedStripOutput(ledId_t num_leds, pinId_t pin, neoPixelType pixel_type_flags) :
	_led(Adafruit_NeoPixel(num_leds, pin, pixel_type_flags))
{
}

void RgbwLedStripOutput::setup()
{
	_led.begin();
}

void RgbwLedStripOutput::flush()
{
	if (_need_flush) {
		_led.show();
		_need_flush = false;
	}
}

void RgbwLedStripOutput::setColor(ledId_t index, rgbw const &color)
{
	_led.setPixelColor(index, color.r, color.g, color.b, color.w);
	_need_flush = true;
}
