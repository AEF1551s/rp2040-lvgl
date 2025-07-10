#if !defined(LV_SCREEN_H)
#define LV_SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "lvgl.h"
#include "lv_port_disp.h"

#include "turtle.h"

static lv_obj_t *label;
static char buf[10];

void screen_init();
void create_centered_number_label();
void update_label_number(unsigned int number);
bool lv_tick(repeating_timer_t *rt);


#endif // LV_SCREEN_H
