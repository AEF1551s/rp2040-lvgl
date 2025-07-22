#include "indicators.h"

static lv_obj_t *indicator_left = NULL;
static lv_obj_t *indicator_right = NULL;

LV_IMG_DECLARE(left_indicator_act);
LV_IMG_DECLARE(left_indicator_emerg);
LV_IMG_DECLARE(left_indicator_empty);

const unsigned int INDICATOR_UPDATE_MS = 700;

const static short int Y_OFFSET = 0;

const static short int indicator_left_x = 5;
const static short int indicator_left_y = Y_OFFSET - 10;

const static short int indicator_right_x = -5;
const static short int indicator_right_y = Y_OFFSET - 10;

void indicators_init(lv_obj_t *screen)
{
    screen = lv_scr_act();

    indicator_left = lv_img_create(screen);
    indicator_right = lv_img_create(screen);
    lv_obj_align(indicator_left, LV_ALIGN_BOTTOM_LEFT, indicator_left_x, indicator_left_y);
    lv_obj_align(indicator_right, LV_ALIGN_BOTTOM_RIGHT, indicator_right_x, indicator_right_y);

    lv_img_set_pivot(indicator_right, left_indicator_act.header.w / 2, left_indicator_act.header.h / 2);
    lv_img_set_angle(indicator_right, 1800);

    lv_img_set_src(indicator_left, &left_indicator_empty);
    lv_img_set_src(indicator_right, &left_indicator_empty);
}

void indicator_right_toogle()
{
    // TODO: implement flashing indicators
    // static bool active = false;
    // if (active == true)
    // {
    //     lv_img_set_src(indicator, &left_indicator_act);
    // }
    // else
    // {
    //     lv_img_set_src(indicator, &left_indicator_empty);
    // }
    // active ^= true;
}

void indicator_left_toogle()
{
    // static bool active = false;
    // if (active == true)
    // {
    //     lv_img_set_src(indicator, &left_indicator_act);
    // }
    // else
    // {
    //     lv_img_set_src(indicator, &left_indicator_empty);
    // }
    // active ^= true;
}

void indicator_timer_init(bool right)
{
    if (right)
    {
        indicator_right_toogle();
    }
    else
    {
        indicator_left_toogle();
    }
}