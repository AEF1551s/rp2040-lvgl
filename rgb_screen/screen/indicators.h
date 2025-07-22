#if !defined(INDICATORS_h)
#define INDICATORS_h

// Contains LEFT, RIGHT, MODE indicators
#include "lv_conf.h"
#include "lvgl.h"
#include "lv_port_disp.h"


void indicators_init(lv_obj_t *screen);
void indicator_timer_init(bool right);
void indicator_right_toogle();
void indicator_left_toogle();
#endif // INDICATORS_h
