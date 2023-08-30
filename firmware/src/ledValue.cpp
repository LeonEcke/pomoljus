
#include "ledValue.hpp"

#include <cmath>

#include "pico/stdlib.h"


static const uint8_t byte_max_value = 0xFF;

struct TempRGB {
	float r, g, b;

	RGB to_rgb() {
		RGB rgb = {(uint8_t)(r * byte_max_value),
				   (uint8_t)(g * byte_max_value),
				   (uint8_t)(b * byte_max_value)};
		return rgb;
	}
};

void RGB::to_rgb(const HSV& hsv) {
	// easy calculations caught first to avoid work
	if (hsv.saturation == 0 || hsv.value == 0) {
		*this = {hsv.value, hsv.value, hsv.value};
	}

	// hue is normalized to ]0, 6[
	const float H = (hsv.hue / 42.5);

	// saturation and value normalized to ]0, 1[
	const float S = hsv.saturation / (float)byte_max_value;
	const float V = hsv.value / (float)byte_max_value;

	const float x = V * (1.0 - S);
	const float y = V * (1.0 - (H - std::floor(H)) * S);
	const float z = V * (1.0 - (1 - (H - std::floor(H))) * S);

	// Depending on hue, xyzV are used differently. See paper for more
	TempRGB temp;
	if ((int)H == 0)
		temp = {V, z, x};
	else if ((int)H == 1)
		temp = {y, V, x};
	else if ((int)H == 2)
		temp = {x, V, z};
	else if ((int)H == 3)
		temp = {x, y, V};
	else if ((int)H == 4)
		temp = {z, x, V};
	else  // (int)H == 5 or 6
		temp = {V, x, y};

	red = temp.r * (float)byte_max_value;
	green = temp.g * (float)byte_max_value;
	blue = temp.b * (float)byte_max_value;
}

uint32_t RGB::to_single_value() const {
	return (red << (8 * 2)) | (green << (8 * 1) | (blue << (8 * 0)));
}

uint8_t my_max(uint8_t a, uint8_t b, uint8_t c) {
	if (a >= b && a >= c) return a;
	if (b >= a && b >= c)
		return b;
	else
		return c;
}

// Couldn't get the max and min functions from <algorithms> working.
uint8_t my_min(uint8_t a, uint8_t b, uint8_t c) {
	if (a <= b && a <= c) return a;
	if (b <= a && b <= c)
		return b;
	else
		return c;
}

void HSV::to_hsv(const RGB& rgb) {
	const uint8_t max = my_max(rgb.red, rgb.green, rgb.blue);
	const uint8_t min = my_min(rgb.red, rgb.green, rgb.blue);

	const uint8_t delta = max - min;

	//? possible issue: hsv.hue is unsigned, yet this can yield negatives

	if (delta == 0)	 // if all colours are equal then saturation is 0
		hue = 0;	 // and hue is undefined. So its set to 0.
	else if (max == rgb.red)
		hue = ((float)(rgb.green - rgb.blue) / delta) * byte_max_value;
	else if (max == rgb.green)
		hue = (((float)(rgb.blue - rgb.red) / delta) + 2) * byte_max_value;
	else if (max == rgb.blue)
		hue = (((float)(rgb.red - rgb.green) / delta) + 4) * byte_max_value;

	value = max;  // value is equal to largest RGB value

	saturation = (value == 0 ? 0 : ((delta / value) * byte_max_value));
}

RGB mix(const RGB& a, const RGB& b, uint8_t factor = 50) {
	// untested
	RGB new_rgb;

	if (factor > 100) factor = 100;

	new_rgb.red = a.red * (100 - factor) + (b.red - a.red) * factor;
	new_rgb.green = a.green * (100 - factor) + (b.green - a.green) * factor;
	new_rgb.blue = a.blue * (100 - factor) + (b.blue - a.blue) * factor;

	return new_rgb;
}

HSV mix(const HSV& a, const HSV& b, uint8_t factor = 50) {
	// untested
	HSV new_hsv;

	new_hsv.hue = a.hue + (b.hue - a.hue) * factor;	 // circular
	new_hsv.saturation =
		a.saturation * (100 - factor) + (b.saturation - a.saturation) * factor;
	new_hsv.value = a.value * (100 - factor) + (b.value - a.value) * factor;

	return new_hsv;
}