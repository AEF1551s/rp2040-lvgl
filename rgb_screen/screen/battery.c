#include "battery.h"

static lv_obj_t *battery = NULL;
const static unsigned int BATT_UPDATE_MS = 1000;

// Battery images
LV_IMG_DECLARE(battery_low);
LV_IMG_DECLARE(battery_25);
LV_IMG_DECLARE(battery_50);
LV_IMG_DECLARE(battery_75);
LV_IMG_DECLARE(battery_full);

const static unsigned int Y_OFFSET = 20;

const static unsigned int battery_x = 10;
const static unsigned int battery_y = Y_OFFSET + 10;

void battery_init(lv_obj_t *screen)
{
    screen = lv_scr_act();

    battery = lv_img_create(screen);
    lv_obj_align(battery, LV_ALIGN_TOP_LEFT, battery_x, battery_y);
    lv_timer_create(update_battery, BATT_UPDATE_MS, NULL);

    // Draw the battery first
    update_battery();
}

void update_battery()
{
    // Set source based on battery level
    // TODO: battery status enum and battery get function
    unsigned int level = 20;
    if (level >= 75)
    {
        lv_img_set_src(battery, &battery_full);
    }
    else if (level >= 50)
    {
        lv_img_set_src(battery, &battery_75);
    }
    else if (level >= 25)
    {
        lv_img_set_src(battery, &battery_50);
    }
    else if (level >= 10)
    {
        lv_img_set_src(battery, &battery_25);
    }
    else
    {
        lv_img_set_src(battery, &battery_low);
    }
}

