#if !defined(BATTERY_H)
#define BATTERY_H

#include "lv_conf.h"
#include "lvgl.h"
#include "lv_port_disp.h"

void battery_init();
void update_battery();

#endif // BATTERY_H
