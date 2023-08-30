#include "ledModifier.hpp"
#include "pico/stdlib.h"
#include <cmath>

static HSV* led_array;
static long* tick;
const int nr_of_leds = 5; //OBS, should be inherrited once linked

static const double pi = 3.14159265359;

void setPointers(HSV *led_array_pointer, long *tick_pointer){
	led_array = led_array_pointer;
	tick = tick_pointer;
}

void setColour(HSV colour, uint8_t bitmask)
{
	for ( int i = 0; i < nr_of_leds; i++ ){
		led_array[i] = colour;
	}
}

void changeHue(HSV &led, int amount){
	led.hue = ( ( led.hue + amount ) + 255) % 255; // looping
}

void changeSaturation(HSV &led, int amount){
	int capped_amount = led.saturation + amount;
	if (capped_amount < 0)
		capped_amount = 0;
	else if (capped_amount > 255)
		capped_amount = 255;
	led.saturation = capped_amount;
}

void changeValue(HSV &led, int amount){
	int capped_amount = led.value + amount;
	if (capped_amount < 0)
		capped_amount = 0;
	else if (capped_amount > 255)
		capped_amount = 255;
	led.value = capped_amount;
}

void breathAnimation(uint16_t period_time_ms, uint8_t variation_amount,
					 uint8_t offset_ms, void (&modification_method)(HSV &led, int amount)){
	long tickCopy = *tick;
	uint8_t breathValue = variation_amount * ( ( sin((tickCopy + offset_ms) * (2 * pi) / period_time_ms) + 1 ) / 2 );
	for (int i = 0; i < nr_of_leds; ++i){
		modification_method(led_array[i], -breathValue);
	}
}

void progressAnimation(uint8_t progress, uint8_t variation_amount,
					   void (&modification_method)(HSV& led, int amount)){
	uint8_t inverse_progress = 255 - progress;

	uint8_t max_progress_per_led = 255 / nr_of_leds;
	uint8_t fully_on_leds = inverse_progress / max_progress_per_led;
	uint8_t fully_off_leds = nr_of_leds - fully_on_leds;

	for (int i = nr_of_leds; i > (fully_off_leds); --i)
		modification_method(led_array[i - 1], -variation_amount);

	modification_method(led_array[fully_off_leds - 1],
		-((inverse_progress % max_progress_per_led) * ((float)variation_amount/(float)max_progress_per_led)));
}