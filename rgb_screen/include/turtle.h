#if !defined(TURTLE_H)
#define TURTLE_H

// Turtle uses TIMER 0 and ALARM 0 for interval based ADC reading and updating the values

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

void turtle_init();
uint get_turtle();

static inline uint clamp_range(uint value, uint low, uint high);
static void alarm_ms_init();
static void alarm_irq(void);

#endif // TURTLE_H
