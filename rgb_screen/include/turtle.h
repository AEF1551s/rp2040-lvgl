#if !defined(TURTLE_H)
#define TURTLE_H

// Turtle uses TIMER 0 and ALARM 0 for interval based ADC reading and updating the values

#include "pico/stdlib.h"
#include "stdbool.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "low_pass_filter.h"

const static uint CLAMP_LOW =1;
const static uint CLAMP_HIGH = 4000;

extern volatile bool filter_needed;

void turtle_init();
void filter_turtle();
uint get_turtle();

static inline uint clamp_range(uint value, uint low, uint high);
static void alarm_ms_init();
static void alarm_irq(void);

#endif // TURTLE_H
