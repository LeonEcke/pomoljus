#ifndef LEDMODIFIER_H
#define LEDMODIFIER_H

#include "ledValue/ledValue.hpp"
#include "pico/stdlib.h"


// Setup functions ============================================================

/// @brief Set pointers to be used by modifier functions
/// @param led_array Leds to be changed.
/// @param tick A progressing tick that time based animations is based on.
void setPointers(HSV* led_array_pointer, long* tick_pointer);


// Static modifiers ===========================================================

/// @brief Set colour of all leds not masked away by bitmask.
/// @param colour Colour to set leds to.
/// @param bitmask Set ones to mask out colour set. Default = `0`
void setColour(HSV colour, uint8_t bitmask = 0 );


// Modification methods =======================================================

/* EXAMPLE:
for (HSV x : led_array){
	new_value = animation_specific_calculation(tick);
	modification_method(x, new_value);
}

This will allow an animation to be applied to either of the 3 HSV values
without needing custom methods for all of them.

By having amount be a signed value, this allows for animations to be both
additive and subtractive where it makes sense.
*/

/// @brief Changes the hue value of a led.
/// @param led Led to be changed.
/// @param amount Amount to be changed by.
void changeHue(HSV& led, int amount);

/// @brief Changes the saturation value of a led.
/// @param led Led to be changed.
/// @param amount Amount to be changed by.
void changeSaturation(HSV& led, int amount);

/// @brief Changes the value (brightness) of a led.
/// @param led Led to be changed.
/// @param amount Amount to be changed by.
void changeValue(HSV& led, int amount);


// Animated modifiers ( uses tick ) ===========================================

/// @brief A subtractive animation that decreases selected value in a sin wave.
/// @param period_time_sec Time for a full sin cycle to be completed.
/// @param variation_amount Maximum change.
/// @param modification_method HSV change method.
void waveAnimation(uint16_t period_time_ms, uint8_t variation_amount,
						uint16_t offset_ms, void (&modification_method)(HSV& led, int amount));

/// @brief A subtractive animation that varies the selected value in and out
///	uniformly over time.
/// @param period_time_sec Time for a full "breath" to be completed.
/// @param variation_amount Maximum change.
/// @param modification_method HSV change method.
void breathAnimation(uint16_t period_time_ms, uint8_t variation_amount,
						uint16_t offset_ms, void (&modification_method)(HSV& led, int amount));

/// @brief A progress bar.
/// @param progress A value `]0, 100[` representing completed percentage.
/// @param variation_amount Maximum change.
/// @param modification_method HSV change method.
void progressAnimation(uint8_t progress, uint8_t variation_amount,
						void (&modification_method)(HSV& led, int amount));

#endif