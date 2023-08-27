#ifndef LEDVALUE_H
#define LEDVALUE_H

#include "pico/stdlib.h"

class RGB; // forward declaration

/*
Dataclass to handle the HSV (hue, saturation, value) formatting of colours
*/
class HSV{
public:
	uint8_t hue, saturation, value;

	/*
	Take an RGB class object and converst it to a HSV class object.
	@return hsv object converted from rgb object
	@attention imperfect conversion!
	@note formula from: https://mattlockyer.github.io/iat455/documents/rgb-hsv.pdf
	*/
	void to_hsv(const RGB& rgb);
};

/*
Dataclass to handle the RGB (red, green, blue) formatting of colours
*/
class RGB{
public:
	uint8_t red, green, blue;

	/*
	Take a HSV class object and converst it to an RGB class object.
	@return rgb object converted from hsv object
	@attention imperfect conversion!
	@note formula from: https://mattlockyer.github.io/iat455/documents/rgb-hsv.pdf
	*/
	void to_rgb(const HSV& hsv);

	/*
	@return a 24 bit value formatted 0xRRGGBB
	*/
	uint32_t to_single_value() const;
};

RGB mix(const RGB &a, const RGB &b, uint8_t factor);
HSV mix(const HSV &a, const HSV &b, uint8_t factor);

#endif