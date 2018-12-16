#include "LedMatrixOutputManager.h"

LedMatrixOutputManager::LedMatrixOutputManager(coord_t width, coord_t height, RgbwLedStripOutput &output) :
	_output(output),
	_width(width),
	_height(height),
	_colors(new rgbwa[width * height * LEDMATRIXOUTPUTMANAGER_NUM_LAYERS])
{
	memset(_colors, 0, width * height * LEDMATRIXOUTPUTMANAGER_NUM_LAYERS * sizeof(rgbwa));

	// Default color of layer 0 is white
	for (int i = 0; i < width * height; ++i)
		_colors[i].color.w = 0xFF;
}

LedMatrixOutputManager::~LedMatrixOutputManager()
{
	delete[] _colors;
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
				rgbw color = _colors[y * _height + x].color;
				for (uint8_t layer = 1; layer < LEDMATRIXOUTPUTMANAGER_NUM_LAYERS; ++layer)
					color = color + _colors[y * _height + x + layer * _width * _height];
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

	coord_t x_mapped_to_topleft_quadrant = flipped_quadrant_x_axis ? (_width / 2 - 1 - x_relative_to_quadrant) : x_relative_to_quadrant;
	coord_t y_mapped_to_topleft_quadrant = flipped_quadrant_y_axis ? (_height / 2 - 1 - y_relative_to_quadrant) : y_relative_to_quadrant;

	switch (10 * y_mapped_to_topleft_quadrant + x_mapped_to_topleft_quadrant)
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

void LedMatrixOutputManager::setColor(coord_t x, coord_t y, uint8_t layer, rgbwa color)
{
	if (0 <= x && x < _width && 0 <= y && y < _height && layer < LEDMATRIXOUTPUTMANAGER_NUM_LAYERS)
	{
		int offset = layer * _width * _height;
		if (_colors[y * _height + x + offset] != color)
		{
			_colors[y * _height + x + offset] = color;
			_need_flush = true;
		}
	}
}
