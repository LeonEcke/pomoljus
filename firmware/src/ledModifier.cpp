#include "ledModifier.hpp"

#include <cmath>

#include "pico/stdlib.h"

static HSV *led_array;
static long *tick;
const int nr_of_leds = 5;  // OBS, should be inherrited once linked

// used to silence intellisenses weird hate for M_PI
static const double pi = 3.14159265359;
static const uint8_t byte_max_value = 0xFF;

void setPointers(HSV *led_array_pointer, long *tick_pointer) {
	led_array = led_array_pointer;
	tick = tick_pointer;
}

void setColour(HSV colour, uint8_t bitmask) {
	for (int i = 0; i < nr_of_leds; i++) {
		led_array[i] = colour;
	}
}

void changeHue(HSV &led, int amount) {
	led.hue = ((led.hue + amount) + byte_max_value) % byte_max_value;	 // looping
}

void changeSaturation(HSV &led, int amount) {
	int capped_amount = led.saturation + amount;
	if (capped_amount < 0)
		capped_amount = 0;
	else if (capped_amount > byte_max_value)
		capped_amount = byte_max_value;
	led.saturation = capped_amount;
}

void changeValue(HSV &led, int amount) {
	int capped_amount = led.value + amount;
	if (capped_amount < 0)
		capped_amount = 0;
	else if (capped_amount > byte_max_value)
		capped_amount = byte_max_value;
	led.value = capped_amount;
}

void waveAnimation(uint16_t period_time_ms, uint8_t variation_amount,
				   uint16_t offset_ms,
				   void (&modification_method)(HSV &led, int amount)) {
	long tickCopy = *tick;
	for (int i = 0; i < nr_of_leds; ++i) {
		uint8_t breathValue =
			variation_amount *
			((sin((tickCopy + (offset_ms * i)) * 
			(2 * pi) / period_time_ms) + 1) / 2);

		modification_method(led_array[i], -breathValue);
	}
}

void breathAnimation(uint16_t period_time_ms, uint8_t variation_amount,
					 uint16_t offset_ms,
					 void (&modification_method)(HSV &led, int amount)) {
	long tickCopy = *tick;
	uint8_t breathValue =
		variation_amount *
		((sin((tickCopy + offset_ms) * (2 * pi) / period_time_ms) + 1) / 2);

	for (int i = 0; i < nr_of_leds; ++i) {
		modification_method(led_array[i], -breathValue);
	}
}

void progressAnimation(uint8_t progress, uint8_t variation_amount,
					   void (&modification_method)(HSV &led, int amount)) {
	// OBS: This is a god ugly function that ought to be refactored

	uint8_t inverse_progress = byte_max_value - progress;
	uint8_t max_progress_per_led = byte_max_value / nr_of_leds;
	uint8_t fully_on_leds = inverse_progress / max_progress_per_led;
	uint8_t fully_off_leds = nr_of_leds - fully_on_leds;

	// turn off fully off leds
	for (int i = nr_of_leds; i > (fully_off_leds); --i)
		modification_method(led_array[i - 1], -variation_amount);

	// set that one led that gradually incerases
	modification_method(
		led_array[fully_off_leds - 1],
		-((inverse_progress % max_progress_per_led) *
		  ((float)variation_amount / (float)max_progress_per_led)));
}