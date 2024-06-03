#ifndef LEDCOTROLLER_H
#define LEDCOTROLLER_H

class Led_controller{
	public:
	Led_controller(int led_pin, int nr_of_leds, int* tick_pointer_ms, int sleep_duration_ms);
	void set_state(/*struct [0, x] or name of state???*/);
	void set_progress(int percentage);
	void start();
	void stop();

	private:
	int _led_pin;
	int _nr_of_leds;
	int* _tick_pointer_ms;
	int _sleep_duration_ms;
};

#endif