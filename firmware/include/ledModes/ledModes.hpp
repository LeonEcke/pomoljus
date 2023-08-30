#ifndef LEDMODES_H
#define LEDMODES_H

#include "ledValue/ledValue.hpp"
#include "pico/stdlib.h"

/*
Loop into one of these to progress animation.
Make sure tickMs is kept updated as well.
*/

void light_mode_setup(HSV* led_array_pointer, long* tick_pointer);

void alarm_light_mode();

void alarm_overtime_light_mode();

void work_light_mode(uint8_t progress);

void short_rest_light_mode(uint8_t progress);

void long_rest_light_mode(uint8_t progress);

#endif