#include "gpio_indicator.h"

volatile bool indicator_left_flag = false;
volatile bool indicator_right_flag = false;
volatile bool indicator_rl_flag = false;

void gpio_indicator_init()
{
    // Setup 3 buttons
    gpio_init(INPUT_LEFT_PIN);
    gpio_set_dir(INPUT_LEFT_PIN, GPIO_IN);
    gpio_pull_up(INPUT_LEFT_PIN);

    gpio_init(INPUT_RIGHT_PIN);
    gpio_set_dir(INPUT_RIGHT_PIN, GPIO_IN);
    gpio_pull_up(INPUT_RIGHT_PIN);

    gpio_set_irq_enabled_with_callback(INPUT_LEFT_PIN, GPIO_IRQ_EDGE_FALL, true, gpio_interrupt); // single gpio interrupt callback (ISR) gets called when gpio IRq happens
    gpio_set_irq_enabled(INPUT_RIGHT_PIN, GPIO_IRQ_EDGE_FALL, true);                              // Enable interrupt for right pin

    // Setup output LEFT, RIGHT indicator
    gpio_init(LEFT_INDICATOR_PIN);
    gpio_init(RIGHT_INDICATOR_PIN);
    gpio_set_dir(LEFT_INDICATOR_PIN, GPIO_OUT);
    gpio_set_dir(RIGHT_INDICATOR_PIN, GPIO_OUT);
}

void gpio_interrupt(uint gpio, uint32_t events)
{

    if (indicator_left_flag || indicator_right_flag)
    {
        return;
    }
    if (gpio == INPUT_LEFT_PIN)
    {
        indicator_left_flag = true;
    }
    if (gpio == INPUT_RIGHT_PIN)
    {
        indicator_right_flag = true;
    }
    gpio_set_irq_enabled(INPUT_LEFT_PIN, GPIO_IRQ_EDGE_FALL, false);
    gpio_set_irq_enabled(INPUT_RIGHT_PIN, GPIO_IRQ_EDGE_FALL, false);
}