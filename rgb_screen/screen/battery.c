#include "battery.h"

static lv_obj_t *battery = NULL;
static const unsigned int BATT_UPDATE_MS = 1000;

// Battery images
LV_IMG_DECLARE(battery_low);
LV_IMG_DECLARE(battery_10);
LV_IMG_DECLARE(battery_25);
LV_IMG_DECLARE(battery_50);
LV_IMG_DECLARE(battery_75);
LV_IMG_DECLARE(battery_full);

static const unsigned int Y_OFFSET = 20;

static const unsigned int battery_x = 0;
static const unsigned int battery_y = Y_OFFSET + 0;

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
    static unsigned int level = 0;
    if (level <= 100 && level >= 85)
    {
        lv_img_set_src(battery, &battery_full);
    }
    else if (level >= 75)
    {
        lv_img_set_src(battery, &battery_75);
    }
    else if (level >= 50)
    {
        lv_img_set_src(battery, &battery_50);
    }
    else if (level >= 25)
    {
        lv_img_set_src(battery, &battery_25);
    }
    else if (level >= 10)
    {
        lv_img_set_src(battery, &battery_10);
    }
    else
    {
        lv_img_set_src(battery, &battery_low);
    }

    level += 10;
    level %= 101;
}
