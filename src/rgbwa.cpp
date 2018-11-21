#include "rgbw.h"
#include "rgbwa.h"

rgbwa const rgbwa::transparent;

rgbw operator+(rgbw const &base, rgbwa const &overlay)
{
	rgbw result;
	result.r = base.r * (1.0 - overlay.a) + overlay.color.r * overlay.a;
	result.g = base.g * (1.0 - overlay.a) + overlay.color.g * overlay.a;
	result.b = base.b * (1.0 - overlay.a) + overlay.color.b * overlay.a;
	result.w = base.w * (1.0 - overlay.a) + overlay.color.w * overlay.a;
	return result;
}

bool operator==(rgbwa const &a, rgbwa const &b)
{
	if (a.a == 0 && b.a == 0)
		return true;
	else
		return a.color == b.color && a.a == b.a;
}

bool operator!=(rgbwa const &a, rgbwa const &b)
{
	if (a.a == 0 && b.a == 0)
		return false;
	else
		return a.color != b.color || a.a != b.a;
}
