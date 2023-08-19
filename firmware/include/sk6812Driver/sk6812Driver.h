#ifndef sk6812Driver_H
#define sk6812Driver_H

#include <stdio.h>
#include "pico/stdlib.h"

#define led_data_output_pin 2
#define nr_of_leds 5

struct colour_value {
	uint32_t hue;
	uint8_t brightness;
};

void sk6812_init();

int sk6812_loop();

#endif