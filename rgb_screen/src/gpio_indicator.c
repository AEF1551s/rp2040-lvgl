#include "gpio_indicator.h"

volatile bool indicator_left_flag = false;
volatile bool indicator_right_flag = false;
volatile bool indicator_rl_flag = false;

void gpio_indicator_init()
{
    // Setup 3 buttons
    gpio_init(LEFT_PIN);
    gpio_set_dir(LEFT_PIN, GPIO_IN);
    gpio_pull_up(LEFT_PIN);

    gpio_init(RIGHT_PIN);
    gpio_set_dir(RIGHT_PIN, GPIO_IN);
    gpio_pull_up(RIGHT_PIN);

    gpio_set_irq_enabled_with_callback(LEFT_PIN, GPIO_IRQ_EDGE_FALL, true, gpio_interrupt); // single gpio interrupt callback (ISR) gets called when gpio IRq happens
    gpio_set_irq_enabled(RIGHT_PIN, GPIO_IRQ_EDGE_FALL, true);                              // Enable interrupt for right pin
}

void gpio_interrupt(uint gpio, uint32_t events)
{

    if (indicator_left_flag || indicator_right_flag)
    {
        return;
    }
    if (gpio == LEFT_PIN)
    {
        indicator_left_flag = true;
    }
    if (gpio == RIGHT_PIN)
    {
        indicator_right_flag = true;
    }
    gpio_set_irq_enabled(LEFT_PIN, GPIO_IRQ_EDGE_FALL, false);
    gpio_set_irq_enabled(RIGHT_PIN, GPIO_IRQ_EDGE_FALL, false);
}