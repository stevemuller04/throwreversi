#ifndef INCLUDE_SRC_CONTROL_LEDMATRIXOUTPUTMANAGER_H
#define INCLUDE_SRC_CONTROL_LEDMATRIXOUTPUTMANAGER_H

#include <Arduino.h>
#include "../Output/RgbwLedStripOutput.h"
#include "../rgbw.h"
#include "../rgbwa.h"
#include "../types.h"

/**
 * Manages the colors of an RGBW led strip arranged as a matrix.
 */
class LedMatrixOutputManager
{
	private:
		coord_t const _width;
		coord_t const _height;
		rgbw * const _base;
		rgbwa * const _overlay;
		bool _need_flush = true;
		RgbwLedStripOutput &_output;

	private:
		/**
		 * Gets the zero-based index of a tile in the order that is induced by the LED strip.
		 * This tile index is referred to as the ID of the contained LEDs.
		 * Note that each tile has two LEDs; the zero-based index of the LED in the LED strip thus corresponds to `2 * ID + 0|1`.
		 * @param x The x coordinate of the tile.
		 * @param y The y coordinate of the tile.
		 */
		ledId_t getLedId(coord_t x, coord_t y) const;

	public:
		/**
		 * Initializes a new LedMatrixOutputManager.
		 * @param width The board width.
		 * @param height The board height.
		 * @param output The LED strip.
		 */
		LedMatrixOutputManager(coord_t width, coord_t height, RgbwLedStripOutput &output);

		/**
		 * Destroys the LedMatrixOutputManager and frees all resources.
		 */
		~LedMatrixOutputManager();

		/**
		 * Makes all changes effective that were made by setBaseColor() and setOverlayColor().
		 */
		void flush();

		/**
		 * Sets the base color for a tile.
		 * If no overlays are specified, this color will be the color displayed by the LED.
		 * @param x The x coordinate of the tile.
		 * @param y The y coordinate of the tile.
		 * @param color The color.
		 */
		void setBaseColor(coord_t x, coord_t y, rgbw color);

		/**
		 * Sets the overlay color for a tile.
		 * The actual color of the LED will be the result of the blending of the base color with the overlay color.
		 * @param x The x coordinate of the tile.
		 * @param y The y coordinate of the tile.
		 * @param color The overlay color.
		 */
		void setOverlayColor(coord_t x, coord_t y, rgbwa color);
};

#endif
