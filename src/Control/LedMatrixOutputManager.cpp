#include "LedMatrixOutputManager.h"

LedMatrixOutputManager::LedMatrixOutputManager(coord_t width, coord_t height, RgbwLedStripOutput *output) :
	_output(output),
	_width(width),
	_height(height)
{
	_base = new rgbw[width * height];
	_overlay = new rgbwa[width * height];
	memset(_base, 0, width * height * sizeof(rgbw));
	memset(_overlay, 0, width * height * sizeof(rgbwa));
}

void LedMatrixOutputManager::flush()
{
	if (_need_flush)
	{
		for (coord_t x = 0; x < _width; x++)
		{
			for (coord_t y = 0; y < _height; y++)
			{
				ledId_t id = getLedId(x, y);
				rgbw color = _base[y * _height + x] + _overlay[y * _height + x];
				_output->setColor(2 * id, color);
				_output->setColor(2 * id + 1, color);
			}
		}
		_need_flush = false;

		_output->flush();
	}
}

ledId_t LedMatrixOutputManager::getLedId(coord_t x, coord_t y) const
{
	switch (10*x+y)
	{
		case 00: return 8;
		case 10: return 7;
		case 20: return 6;
		case 21: return 5;
		case 11: return 4;
		case 01: return 3;
		case 02: return 2;
		case 12: return 1;
		case 22: return 0;
		default: return 9;
	}
}

void LedMatrixOutputManager::setBaseColor(coord_t x, coord_t y, rgbw color)
{
	if (0 <= x && x < _width && 0 <= y && y < _height)
	{
		if (_base[y * _height + x] != color)
		{
			_base[y * _height + x] = color;
			_need_flush = true;
		}
	}
}

void LedMatrixOutputManager::setOverlayColor(coord_t x, coord_t y, rgbwa color)
{
	if (0 <= x && x < _width && 0 <= y && y < _height)
	{
		if (_overlay[y * _height + x] != color)
		{
			_overlay[y * _height + x] = color;
			_need_flush = true;
		}
	}
}
