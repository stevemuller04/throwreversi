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
		coord_t _width;
		coord_t _height;
		rgbw *_base;
		rgbwa *_overlay;
		bool _need_flush = true;
		RgbwLedStripOutput *_output;

	private:
		ledId_t getLedId(coord_t x, coord_t y) const;

	public:
		LedMatrixOutputManager(coord_t width, coord_t height, RgbwLedStripOutput *output);
		~LedMatrixOutputManager();
		void flush();
		void setBaseColor(coord_t x, coord_t y, rgbw color);
		void setOverlayColor(coord_t x, coord_t y, rgbwa color);
};

#endif
