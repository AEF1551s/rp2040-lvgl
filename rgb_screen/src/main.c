
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "throttle.h"
#include "motor.h"
#include "indicators.h"

#include "lv_screen.h"

#include "time.h"
int main()
{
    stdio_init_all();
    screen_init();
    turtle_init();
    motor_init();

    while (true)
    {
        lv_timer_handler(); // Required for LVGL to refresh GUI

        if (filter_needed)
        {
            filter_turtle();
        }
        if (indicator_right_flag)
        {
            indicator_timer_init(1);
            // printf("RIGHT_INDICATOR\n");
        }
        if (indicator_left_flag)
        {
            indicator_timer_init(0);
            // printf("LEFT_INDICATOR\n");
        }
    }
}