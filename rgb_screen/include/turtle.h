#if !defined(TURTLE_H)
#define TURTLE_H

// Turtle uses TIMER 0 and ALARM 0 for interval based ADC reading and updating the values

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

const static uint ADC_PIN = 26;
const static uint ADC_CHANNEL = 0;
const static uint TIMER_NUM = 0;
const static uint ALARM_NUM = 0;
const static uint ALARM_IRQ = 0;
const static uint32_t PERIOD_MS = 1;
const static uint CLAMP_LOW = 3000;
const static uint CLAMP_HIGH = 4000;

static volatile uint16_t adc_value = 0; // Store ADC value updated by timer

void turtle_init();
uint get_turtle();

static inline uint clamp_range(uint value, uint low, uint high);
static void alarm_ms_init();
static void alarm_irq(void);

#endif // TURTLE_H
