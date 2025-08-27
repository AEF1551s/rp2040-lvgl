#if !defined(BATTERY_H)
#define BATTERY_H

#include "lv_conf.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "hardware/adc.h"
#include "hardware/irq.h"
#include <stdio.h>

#define BATTERY_ADC_PIN 27

void battery_init(lv_obj_t *screen);
void update_battery();

#endif // BATTERY_H
