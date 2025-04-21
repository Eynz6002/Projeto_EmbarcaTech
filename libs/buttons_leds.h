#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>

#define button_A 5
#define button_B 6
#define led_green 11
#define led_blue 12
#define led_red 13

void init_buttons();
void init_leds();
void on_green(uint32_t on_time, uint32_t end_time);
void on_blue(uint32_t on_time, uint32_t end_time);
void on_red(uint32_t on_time, uint32_t end_time);

#endif