#if !defined(GPIO_INDICATOR_H)
#define GPIO_INDICATOR_H

#include "lv_conf.h"
#include "lvgl.h"
#include "lv_port_disp.h"

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include <stdio.h>

#define INPUT_LEFT_PIN 4
#define INPUT_MIDDLE_PIN 7
#define INPUT_RIGHT_PIN 11

#define LEFT_INDICATOR_PIN 14
#define RIGHT_INDICATOR_PIN 15

extern volatile bool indicator_left_flag;
extern volatile bool indicator_right_flag;
extern volatile bool indicator_rl_flag;

void gpio_indicator_init();
void gpio_interrupt(uint gpio, uint32_t events);

__always_inline static void indicator_irq_ctrl(bool right, bool left, bool irq)
{
    if (right)
    {
        gpio_set_irq_enabled(INPUT_RIGHT_PIN, GPIO_IRQ_EDGE_FALL, irq);
    }
    if (left)
    {
        gpio_set_irq_enabled(INPUT_LEFT_PIN, GPIO_IRQ_EDGE_FALL, irq);
    }
}

#endif // GPIO_INDICATOR_H
