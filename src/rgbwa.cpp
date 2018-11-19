#include "rgbw.h"
#include "rgbwa.h"

rgbw operator+(rgbw const &base, rgbwa const &overlay)
{
	rgbw result;
	result.r = base.r * (1.0 - overlay.a) + overlay.color.r * overlay.a;
	result.g = base.g * (1.0 - overlay.a) + overlay.color.g * overlay.a;
	result.b = base.b * (1.0 - overlay.a) + overlay.color.b * overlay.a;
	result.w = base.w * (1.0 - overlay.a) + overlay.color.w * overlay.a;
	return result;
}
