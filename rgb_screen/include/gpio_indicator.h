#if !defined(GPIO_INDICATOR_H)
#define GPIO_INDICATOR_H

#include "lv_conf.h"
#include "lvgl.h"
#include "lv_port_disp.h"

extern volatile bool indicator_left_flag;
extern volatile bool indicator_right_flag;

#endif // GPIO_INDICATOR_H
