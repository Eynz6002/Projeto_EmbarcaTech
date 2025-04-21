#ifndef BUZZER_PWM_H
#define BUZZER_PWM_H

#include <stdint.h>

#define buzzer_pwm_pin 21
#define frequency 342
#define duration 1000

void pwm_init_buzzer();
void on_buzzer();

#endif
