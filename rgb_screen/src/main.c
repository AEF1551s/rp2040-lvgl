
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "turtle.h"
#include "motor.h"
#include "indicators.h"
#include "gpio_indicator.h"

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
            indicator_timer_init(true);
        }
        if (indicator_left_flag)
        {
            indicator_timer_init(false);
        }
    }
}