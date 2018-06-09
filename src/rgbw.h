#ifndef INCLUDE_SRC_RGBW_H
#define INCLUDE_SRC_RGBW_H

#include <Arduino.h>

/**
 * Structure representing a color in the red-green-blue-white color space.
 * Each component ranges from 0 to 255 (incl.).
 */
struct rgbw
{
	/** Initializes a default color (black). */
	rgbw(): r(0), g(0), b(0), w(0) { }

	/** Initializes a color using only the RGB components (white is turned off). */
	rgbw(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b), w(0) { }

	/** Initializes a color. */
	rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w): r(r), g(g), b(b), w(w) { }

	/** The red component of the color. */
	uint8_t r;

	/** The green component of the color. */
	uint8_t g;

	/** The blue component of the color. */
	uint8_t b;

	/** The white component of the color. */
	uint8_t w;

	/** The color 'black' (R=G=B=W=0). */
	static rgbw const black;
};

#endif
