#if !defined(LV_SCREEN_H)
#define LV_SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "lvgl.h"
#include "lv_port_disp.h"

#include "turtle.h"

static void alarm_ms_init();
static void lv_tick_irq(void);

void screen_init();
void create_centered_number_label();
void update_label_number(unsigned int number);

#endif // LV_SCREEN_H
