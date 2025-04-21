#include "libs/buzzer_pwm.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <stdint.h>

void pwm_init_buzzer()
{
    gpio_set_function(buzzer_pwm_pin, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(buzzer_pwm_pin);

    pwm_config config = pwm_get_default_config();

    pwm_config_set_clkdiv(&config, 4.0f);

    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(buzzer_pwm_pin, 0);
}
void on_buzzer()
{
    uint slice_num = pwm_gpio_to_slice_num(buzzer_pwm_pin);
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint32_t tone = (clock_freq/frequency) - 1;

    pwm_set_wrap(slice_num, tone);

    //Buzzer with 50% of volume
    pwm_set_gpio_level(buzzer_pwm_pin, tone / 2);
    sleep_ms(duration);
    
    //Buzzer of
    pwm_set_gpio_level(buzzer_pwm_pin, 0);
    sleep_ms(50);
}