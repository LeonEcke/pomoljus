#include "pico/stdlib.h"
#include <stdio.h>

#include <ledController/ledController.hpp>

int main() {

	const int LED_PIN = 25;

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	int count = 0;
	uint8_t flipflop = 0;

	int tickPtr = 0;
	Led_controller led_controller = Led_controller(2, 5, &tickPtr, 100);

	while(1){
		
		//sk6812_loop();
		

		if ( count == 0 ){
			gpio_put(LED_PIN, flipflop);
			flipflop = ((flipflop == 1) ? 0 : 1);
		}
		count = ((count + 1) % 50);
		sleep_ms(10);
	}
}