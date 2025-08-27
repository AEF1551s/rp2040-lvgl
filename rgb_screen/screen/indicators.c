#include "indicators.h"

static lv_obj_t *indicator_left = NULL;
static lv_obj_t *indicator_right = NULL;
static lv_timer_t *timer;

LV_IMG_DECLARE(left_indicator_act);
LV_IMG_DECLARE(left_indicator_emerg);
LV_IMG_DECLARE(left_indicator_empty);

const unsigned int INDICATOR_UPDATE_MS = 333;

static const short int Y_OFFSET = 0;

static const short int indicator_left_x = 5;
static const short int indicator_left_y = Y_OFFSET - 10;

static const short int indicator_right_x = -5;
static const short int indicator_right_y = Y_OFFSET - 10;

static bool indicator_active = false;

#define INDICATOR_UPDATE_COUNT (unsigned int)6
static_assert(INDICATOR_UPDATE_COUNT % 2 == 0, "INDICATOR_UPDATE_COUNT must be divisible by 2!");

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

    gpio_indicator_init();
}

void indicator_right_toogle()
{
    static unsigned int count = 0;
    if (count % 2 == 0)
    {
        lv_img_set_src(indicator_right, &left_indicator_act);
        gpio_put(RIGHT_INDICATOR_PIN, 1);
    }
    else
    {
        lv_img_set_src(indicator_right, &left_indicator_empty);
        gpio_put(RIGHT_INDICATOR_PIN, 0);
    }
    count++;
    if (count >= INDICATOR_UPDATE_COUNT)
    {
        indicator_active = false;
        indicator_right_flag = false;
        count = 0;
        indicator_irq_ctrl(true, true, true);
        gpio_put(RIGHT_INDICATOR_PIN, 0);
    }
}

void indicator_left_toogle()
{
    static unsigned int count = 0;
    if (count % 2 == 0)
    {
        lv_img_set_src(indicator_left, &left_indicator_act);
        gpio_put(LEFT_INDICATOR_PIN, 1);
    }
    else
    {
        lv_img_set_src(indicator_left, &left_indicator_empty);
        gpio_put(LEFT_INDICATOR_PIN, 0);
    }
    count++;
    if (count >= INDICATOR_UPDATE_COUNT)
    {
        indicator_active = false;
        indicator_left_flag = false;
        count = 0;
        indicator_irq_ctrl(true, true, true);
        gpio_put(LEFT_INDICATOR_PIN, 0);
    }
}
lv_timer_cb_t timer_callback;

void indicator_timer_init(bool right)
{
    if (!indicator_active)
    {

        indicator_active = true;

        if (right)
        {
            timer_callback = indicator_right_toogle;
        }
        else
        {
            timer_callback = indicator_left_toogle;
        }

        timer = lv_timer_create(timer_callback, INDICATOR_UPDATE_MS, NULL);
        timer->repeat_count = INDICATOR_UPDATE_COUNT;
    }
}