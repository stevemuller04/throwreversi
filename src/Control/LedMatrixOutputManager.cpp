#include "LedMatrixOutputManager.h"

LedMatrixOutputManager::LedMatrixOutputManager(coord_t width, coord_t height, RgbwLedStripOutput *output) :
	_output(output),
	_width(width),
	_height(height)
{
}

void LedMatrixOutputManager::loop()
{
	if (_need_flush)
	{
		for (coord_t x = 0; x < _width; x++)
			for (coord_t y = 0; y < _height; y++)
				_output->setColor(getLedId(x, y), _base[x, y] + _overlay[x, y]);
		_need_flush = false;
	}
}

ledId_t LedMatrixOutputManager::getLedId(coord_t x, coord_t y) const
{
	return y * _height + x;
}

void LedMatrixOutputManager::setBaseColor(coord_t x, coord_t y, rgbw color)
{
	if (0 <= x && x < _width && 0 <= y && y < _height)
		_base[x, y] = color;
}

void LedMatrixOutputManager::setOverlayColor(coord_t x, coord_t y, rgbwa color)
{
	if (0 <= x && x < _width && 0 <= y && y < _height)
		_overlay[x, y] = color;
}
