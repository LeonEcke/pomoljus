#include "ledController.hpp"

#include "ledModes/ledModes.hpp"
#include "pico/stdlib.h"
#include "sk6812Driver/sk6812Driver.hpp"

Led_controller::Led_controller(int led_pin, int nr_of_leds, int* tick_pointer_ms, int sleep_duration_ms){
	_led_pin			= led_pin;
	_nr_of_leds			= nr_of_leds;
	_tick_pointer_ms	= tick_pointer_ms;
	_sleep_duration_ms	= sleep_duration_ms;

	sk6812_init(_led_pin, _nr_of_leds);
}