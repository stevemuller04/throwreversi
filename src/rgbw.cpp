#include "rgbw.h"

rgbw const rgbw::black;

bool operator==(rgbw const &a, rgbw const &b)
{
	return a.r == b.r && a.g == b.g && a.b == b.b;
}

bool operator!=(rgbw const &a, rgbw const &b)
{
	return a.r != b.r || a.g != b.g || a.b != b.b;
}
