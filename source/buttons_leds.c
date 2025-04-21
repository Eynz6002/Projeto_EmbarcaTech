#include "libs/buttons_leds.h"
#include "pico/stdlib.h"

void on_green(uint32_t on_time, uint32_t end_time)
{
    gpio_put(led_green, true);

    sleep_ms(on_time);

    gpio_put(led_green, false);

    sleep_ms(end_time);
}
void on_blue(uint32_t on_time, uint32_t end_time)
{
    gpio_put(led_blue, true);

    sleep_ms(on_time);

    gpio_put(led_blue, false);

    sleep_ms(end_time);
}
void on_red(uint32_t on_time, uint32_t end_time)
{
    gpio_put(led_red, true);

    sleep_ms(on_time);

    gpio_put(led_red, false);

    sleep_ms(end_time);
}
void init_leds()
{
    gpio_init(led_green);
    gpio_set_dir(led_green, GPIO_OUT);
    gpio_put(led_green, false);
    gpio_init(led_blue);
    gpio_set_dir(led_blue, GPIO_OUT);
    gpio_put(led_blue, false);
    gpio_init(led_red);
    gpio_set_dir(led_red, GPIO_OUT);
    gpio_put(led_red, false);
}
void init_buttons()
{
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);
    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);
}