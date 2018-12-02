#include "LedMatrixOutputManager.h"

LedMatrixOutputManager::LedMatrixOutputManager(coord_t width, coord_t height, RgbwLedStripOutput &output) :
	_output(output),
	_width(width),
	_height(height),
	_base(new rgbw[width * height]),
	_overlay(new rgbwa[width * height])
{
	memset(_base, 0, width * height * sizeof(rgbw));
	memset(_overlay, 0, width * height * sizeof(rgbwa));

	for (int i = 0; i < width * height; ++i)
		_base[i].w = 0xFF;
}

LedMatrixOutputManager::~LedMatrixOutputManager()
{
	delete[] _overlay;
	delete[] _base;
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
				_output.setColor(2 * id, color);
				_output.setColor(2 * id + 1, color);
			}
		}
		_need_flush = false;
	}
}

ledId_t LedMatrixOutputManager::getLedId(coord_t x, coord_t y) const
{
	// The board is split into 4 quadrants.
	// Order of quadrants: top-left, top-right, bottom-right, bottom-left
	// Board origin (x=0, y=0): top-most left-most tile
	// The LEDs are numbered as follows:
	/*
	  ┌──┬──┬──┐   ┌──┬──┬──┐
	  │ 6│ 7│ 8│ → │ 9│10│11│
	  ├──┼──┼──┤   ├──┼──┼──┤
	  │ 5│ 4│ 3│   │14│13│12│
	  ├──┼──┼──┤   ├──┼──┼──┤
	→ │ 0│ 1│ 2│   │15│16│17│
	  └──┴──┴──┘   └──┴──┴──┘
	                       ↓
	  ┌──┬──┬──┐   ┌──┬──┬──┐
	  │35│34│33│   │20│19│18│
	  ├──┼──┼──┤   ├──┼──┼──┤
	  │30│31│32│   │21│22│23│
	  ├──┼──┼──┤   ├──┼──┼──┤
	  │29│28│27│ ← │26│25│24│
	  └──┴──┴──┘   └──┴──┴──┘
	*/

	ledId_t quadrant_led_offset =
		x < _width / 2 /*left*/ ?
			(y < _height / 2 /*top*/ ? 0 : 27) :
			(y < _height / 2 /*top*/ ? 9 : 18);
	bool flipped_quadrant_x_axis = y >= _height / 2;
	bool flipped_quadrant_y_axis = x >= _width / 2;
	coord_t x_relative_to_quadrant = x % (_width / 2);
	coord_t y_relative_to_quadrant = y % (_width / 2);

	coord_t x_mapped_to_topleft_quadrant = flipped_quadrant_x_axis ? (_width / 2 - x_relative_to_quadrant) : x_relative_to_quadrant;
	coord_t y_mapped_to_topleft_quadrant = flipped_quadrant_y_axis ? (_height / 2 - y_relative_to_quadrant) : y_relative_to_quadrant;

	switch (10 * y + x)
	{
		case 00: return 6 + quadrant_led_offset;
		case 01: return 7 + quadrant_led_offset;
		case 02: return 8 + quadrant_led_offset;
		case 10: return 5 + quadrant_led_offset;
		case 11: return 4 + quadrant_led_offset;
		case 12: return 3 + quadrant_led_offset;
		case 20: return 0 + quadrant_led_offset;
		case 21: return 1 + quadrant_led_offset;
		case 22: return 2 + quadrant_led_offset;
		default: return _width * _height;
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
