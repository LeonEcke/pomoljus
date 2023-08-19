#include "sk6812Driver.h"

// Needed for PIO operation of SK6812s
#define _USE_MATH_DEFINES
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "sk6812.pio.h"

int my_brightness = 3;

struct colour_value led_array[nr_of_leds];

static inline void put_pixel(uint32_t pixel_grb) {
	pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
	return
			((uint32_t) (r) << 8) |
			((uint32_t) (g) << 16) |
			(uint32_t) (b);
}

uint32_t hue_brightness_to_rgb(struct colour_value hue_brightness){

	// https://www.desmos.com/calculator/bbpxleqvoa for demo?

	/* Hue is calculated from a 3 phase sine wave.	 Offset the colours by 1/3 period.   Use the brightness as amplitude.
	*		   |														 |						  |
	*		   |	  Value origin.   Set the phase period to 255 units. |  Set range to [0, 255] |	  		 Range to [0, 255]
	*		   |		   |					   |					 |			   |		  |				     	 | */
	int r = ( sin( (hue_brightness.hue * ((2 * M_PI) / 255.0) ) + ((0 * M_PI) / 3) ) + 1 ) * hue_brightness.brightness * 8;
	int g = ( sin( (hue_brightness.hue * ((2 * M_PI) / 255.0) ) + ((2 * M_PI) / 3) ) + 1 ) * hue_brightness.brightness * 8;
	int b = ( sin( (hue_brightness.hue * ((2 * M_PI) / 255.0) ) + ((4 * M_PI) / 3) ) + 1 ) * hue_brightness.brightness * 8;

	return (urgb_u32(r, g, b));
}

void set_leds(struct colour_value led_values[]){

	for (int i = 0; i < nr_of_leds; ++i)
		put_pixel(hue_brightness_to_rgb(led_values[i]));

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

	for (int i = 0; i < nr_of_leds; ++i){
		led_array[i].hue = 0;
		led_array[i].brightness = my_brightness;
	}
}

int sk6812_loop(){
	static int t = 0;
    static int binary_counter = 0;
    static int ix = 0;



	for (int i = 0; i < nr_of_leds; ++i){
		led_array[i].hue = (t + (i * 20)) % 255;
	}
	set_leds(led_array);
	
	++t;
	if (t >= 255)
		t = 0;
    ++ix;
    if (ix % 50 == 0){
        ++binary_counter;
        for (int i = 0; i < nr_of_leds; ++i){
            if ( ( binary_counter & ( 1U << i ) ) != 0 )
                led_array[i].brightness = my_brightness;
            else
                led_array[i].brightness = 1;
        }
    }
	sleep_ms(10);
}