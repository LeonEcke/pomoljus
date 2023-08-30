#include "sk6812Driver.hpp"

// Needed for PIO operation of SK6812s

#include <cmath>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "sk6812.pio.h"
#include "ledValue/ledValue.hpp"
#include "ledModifier/ledModifier.hpp"

int my_brightness = 100;

struct HSV led_array[nr_of_leds];

absolute_time_t tick;
long tickMs;

static inline void put_pixel(uint32_t pixel_grb) {
	pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
	return
			((uint32_t) (r) << 8) |
			((uint32_t) (g) << 16) |
			(uint32_t) (b);
}

void set_leds(){
	RGB rgb;
	for (int i = 0; i < nr_of_leds; ++i){
		rgb.to_rgb(led_array[i]);
		put_pixel(urgb_u32(rgb.red, rgb.green, rgb.blue));
	}
}

void sk6812_init(){
	stdio_init_all();

		// todo get free sm
	PIO pio = pio0;
	int sm = 0;
	int offset = pio_add_program(pio, &sk6812_program);

	// changed clock speed to output correct signal widths
	// TODO: Show calculation for the clk Hz
	sk6812_program_init(pio, sm, offset, led_data_output_pin, 550000);

	setPointers(led_array, &tickMs);
}

void sk6812_loop(){

	static uint8_t ix = 0;

	tick = get_absolute_time();
	tickMs = to_ms_since_boot(tick);

	HSV setLed = {0, 255, 100};
	setColour(setLed);

	waveAnimation(10000, 200, 400, changeHue);

	breathAnimation(5000, 255, 0, changeSaturation);

	progressAnimation(ix, 100, changeValue);
	set_leds();
	ix++;
	ix %= 255;
	sleep_ms(10);
}