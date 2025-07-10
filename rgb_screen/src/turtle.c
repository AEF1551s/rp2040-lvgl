#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"

#define ADC_PIN 26
#define ADC_CHANNEL 0

volatile uint16_t adc_value = 0;

// Timer callback function
bool adc_timer_callback(repeating_timer_t *rt) {
    adc_select_input(ADC_CHANNEL);
    adc_value = adc_read();
    return true;  // return true to keep repeating
}

void turtle_init() {
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_CHANNEL);

    static repeating_timer_t timer;
    // 5000 µs = 5 ms = 200 Hz
    add_repeating_timer_us(-5000, adc_timer_callback, NULL, &timer);
}

unsigned int get_turtle() {
    return adc_value;
}
