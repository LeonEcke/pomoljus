#ifndef LEDMODES_H
#define LEDMODES_H

#include "ledValue/ledValue.hpp"
#include "pico/stdlib.h"

/*
Loop into one of these to progress animation.
Make sure tickMs is kept updated as well.
*/

/// @brief Sets pointers used by led modifier functions
/// @param led_array_pointer Pointer to first index in led array
/// @param tick_pointer Pointer to tick counter. OBS in milliseconds!
void light_mode_setup(HSV* led_array_pointer, long* tick_pointer);

/// @brief A stronger glow and rapid breathing red and orange
void alarm_light_mode();

/// @brief A calmer breathing animation of red and orange
void alarm_overtime_light_mode();

/// @brief A blue progress bar with slight hue shifts
/// @param progress `]0, 255[` value of progress completed.
void work_light_mode(uint8_t progress);


/// @brief A green progress bar with slight hue shifts
/// @param progress `]0, 255[` value of progress completed.
void short_rest_light_mode(uint8_t progress);


/// @brief A yellow progress bar with slight hue shifts
/// @param progress `]0, 255[` value of progress completed.
void long_rest_light_mode(uint8_t progress);

#endif