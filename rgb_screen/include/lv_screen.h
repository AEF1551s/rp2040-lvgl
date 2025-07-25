#if !defined(LV_SCREEN_H)
#define LV_SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "battery.h"
#include "indicators.h"

#include "throttle.h"

void screen_init();

void create_centered_number_label();
void update_speed();

#endif // LV_SCREEN_H
