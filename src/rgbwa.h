#ifndef INCLUDE_SRC_RGBWA_H
#define INCLUDE_SRC_RGBWA_H

#include <Arduino.h>
#include "rgbw.h"

/**
 * Structure representing a color with alpha channel (transparency).
 */
struct rgbwa
{
	/** Initializes a default color (transparent). */
	rgbwa(): color(rgbw::black), a(0.0) { }

	/** Initializes an opaque color (i.e. a = 1.0). */
	rgbwa(rgbw color): color(color), a(1.0) { }

	/** Initializes a transparent color. */
	rgbwa(rgbw color, float a): color(color), a(a) { }

	/** Initializes a transparent color. */
	rgbwa(uint8_t r, uint8_t g, uint8_t b, uint8_t w, float a): color(r, g, b, w), a(a) { }

	/** The actual color. */
	rgbw color;

	/** The alpha component of the color, ranging from 0.0 (transparent) to 1.0 (opaque). */
	float a;

	/** A transparent color (A=0). */
	static rgbwa const transparent;
};

rgbw operator+(rgbw const &base, rgbwa const &overlay);
bool operator==(rgbwa const &a, rgbwa const &b);
bool operator!=(rgbwa const &a, rgbwa const &b);

#endif
