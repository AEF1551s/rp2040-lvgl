#if !defined(TURTLE_H)
#define TURTLE_H

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

const static uint ADC_PIN = 26;
const static uint ADC_CHANNEL = 0;
const static uint ALARM_NUM = 0;

#define ALARM_IRQ timer_hardware_alarm_get_irq_num(timer_hw, ALARM_NUM)

static volatile uint16_t adc_value = 0;  // Store ADC value updated by timer

void turtle_init();
unsigned int get_turtle();

static void alarm_in_us(uint32_t delay_us);
static void alarm_irq(void);

#endif // TURTLE_H

