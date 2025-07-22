#include "turtle.h"

static uint ADC_PIN = 26;
const static uint ADC_CHANNEL = 0;
const static uint TIMER_NUM = 0;
const static uint ALARM_NUM = 0;
const static uint ALARM_IRQ = 0;
const static uint32_t PERIOD_MS = 1;

static volatile uint16_t adc_value = 0; // Store ADC value updated by timer

static void alarm_ms_init()
{
    // Enable the interrupt for our alarm (the timer outputs 4 alarm irqs)
    hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM);
    // Set irq handler for alarm irq
    irq_set_exclusive_handler(ALARM_IRQ, alarm_irq);
    // Enable the alarm irq
    irq_set_enabled(ALARM_IRQ, true);

    // Alarm is only 32 bits so if trying to delay more
    // than that need to be careful and keep track of the upper
    // bits
    uint64_t target = timer_hw->timerawl + (PERIOD_MS * 1000);

    // Write the lower 32 bits of the target time to the alarm which
    // will arm it
    timer_hw->alarm[ALARM_NUM] = (uint32_t)target;
}

static void alarm_irq(void)
{
    static uint64_t target = 0;
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);
    target = timer_hw->timerawl + (PERIOD_MS * 1000);
    timer_hw->alarm[ALARM_NUM] = (uint32_t)target;

    adc_select_input(ADC_CHANNEL);
    adc_value = adc_read();
}

void turtle_init()
{
    adc_init();
    adc_gpio_init(ADC_PIN);
    alarm_ms_init();
}

static inline uint clamp_range(uint value, uint low, uint high)
{
    uint result = 0;

    if (value < low)
    {
        result = low;
    }
    else if (value > high)
    {
        result = high;
    }
    else
    {
        result = value;
    }

    return result;
}

inline uint get_turtle()
{
    uint result = clamp_range(adc_value, CLAMP_LOW, CLAMP_HIGH);
    result = low_pass_filter(result);
    result = clamp_range(result, CLAMP_LOW, CLAMP_HIGH); //Quick fix so lp filter doesnt return less then clamp low due to FP losses
    
    return result;
}
