#include "ledModes.hpp"
#include "ledModifier/ledModifier.hpp"
#include "ledValue/ledValue.hpp"
#include "pico/stdlib.h"

uint8_t default_value = 100;

enum colours{
	red = 0,
	orange = 17,
	yellow = 43,
	green = 80,
	blue = 150,
	magenta = 190
};

void light_mode_setup(HSV* led_array_pointer, long* tick_pointer) {
	setPointers( led_array_pointer, tick_pointer);
}

void work_light_mode(uint8_t progress) {
	const static HSV background = {blue, 255, default_value};
	setColour(background);
	waveAnimation(1000, 10, 700, changeHue);
	progressAnimation(progress, default_value, changeValue);
}
