#include "ledModifier.hpp"
#include "pico/stdlib.h"

static HSV* led_array;
static long& tick;
const int nr_of_leds = 5; //OBS, should be inherrited once linked

void setPointers(HSV led_array_pointer[], long& tick_pointer){
	led_array = led_array_pointer;
	tick = tick_pointer;
}

void setColour(HSV colour, uint8_t bitmask){
	for ( int i = 0; i < nr_of_leds; i++ ){
		led_array[i] = colour;
	}
}

void changeHue(HSV &led, int amount){
	led.hue = ( led.hue + amount ) % 255; // looping
}

void changeSaturation(HSV &led, int amount){
	int capped_amount = led.saturation + amount;
	if (capped_amount < 0)
		capped_amount = 0;
	else if (capped_amount > 255)
		capped_amount = 255;
	led.saturation += capped_amount;
}

void changeValue(HSV &led, int amount){
	int capped_amount = led.value + amount;
	if (capped_amount < 0)
		capped_amount = 0;
	else if (capped_amount > 255)
		capped_amount = 255;
	led.value += capped_amount;
}
