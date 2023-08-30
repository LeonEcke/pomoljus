#include "ledModes.hpp"

#include "ledModifier/ledModifier.hpp"
#include "ledValue/ledValue.hpp"
#include "pico/stdlib.h"

static const uint8_t byte_max_value = 0xFF;
uint8_t default_value = 100;
uint8_t alarm_value = 200;

enum colours {
	red = 0,
	orange = 17,
	yellow = 43,
	green = 80,
	blue = 150,
	magenta = 190
};

void light_mode_setup(HSV* led_array_pointer, long* tick_pointer) {
	setPointers(led_array_pointer, tick_pointer);
}

void alarm_light_mode() {
	const static HSV background = {orange, byte_max_value, alarm_value};
	setColour(background);
	
	// most litterals below are based purely on feel
	breathAnimation(700, alarm_value - (alarm_value / 7), 0, changeValue);
	waveAnimation(500, 17, 300, changeHue);
}

void alarm_overtime_light_mode() {
	const static HSV background = {orange, byte_max_value, default_value};
	setColour(background);
	
	// most litterals below are based purely on feel
	waveAnimation(1000, 17, 300, changeHue);
	breathAnimation(5000, default_value - (default_value / 4), 0, changeValue);
}

/// @brief Generic progress function for internal use.
void generic_progress_light_mode(uint8_t progress, uint8_t background_hue) {
	const static HSV background = {background_hue, byte_max_value, default_value};
	setColour(background);
	
	// most litterals below are based purely on feel
	waveAnimation(1000, 10, 700, changeHue);
	progressAnimation(progress, default_value - (default_value / 4),
					  changeValue);
	progressAnimation(progress, default_value - (default_value / 2),
					  changeSaturation);
}

void work_light_mode(uint8_t progress) {
	generic_progress_light_mode(progress, blue);
}

void short_rest_light_mode(uint8_t progress) {
	generic_progress_light_mode(progress, green);
}

void long_rest_light_mode(uint8_t progress) {
	generic_progress_light_mode(progress, yellow);
}
