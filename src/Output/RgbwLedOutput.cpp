#include "RgbwLedOutput.h"

RgbwLedOutput::RgbwLedOutput(pinId_t pin, neoPixelType pixel_type_flags) :
	RgbwLedStripOutput(1, pin, pixel_type_flags)
{
}

void RgbwLedOutput::setColor(rgbw const &color)
{
	RgbwLedStripOutput::setColor(0, color);
}
