#if !defined(GPIO_INDICATOR_H)
#define GPIO_INDICATOR_H

#include "lv_conf.h"
#include "lvgl.h"
#include "lv_port_disp.h"

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include <stdio.h>

#define LEFT_PIN 4
#define MIDDLE_PIN 7
#define RIGHT_PIN 11

extern volatile bool indicator_left_flag;
extern volatile bool indicator_right_flag;
extern volatile bool indicator_rl_flag;

void gpio_indicator_init();
void gpio_interrupt(uint gpio, uint32_t events);

__always_inline static void indicator_irq_ctrl(bool right, bool left, bool irq)
{
    if (right)
    {
        gpio_set_irq_enabled(RIGHT_PIN, GPIO_IRQ_EDGE_FALL, irq);
    }
    if (left)
    {
        gpio_set_irq_enabled(LEFT_PIN, GPIO_IRQ_EDGE_FALL, irq);
    }
}

#endif // GPIO_INDICATOR_H
