#if !defined(MOTOR_H)
#define MOTOR_H

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#include "turtle.h"

void motor_init();

#endif // MOTOR_H
