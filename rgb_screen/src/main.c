
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "turtle.h"

#include "lv_screen.h"

int main()
{
    stdio_init_all();
    screen_init();
    turtle_init();

    while (true)
    {
        lv_timer_handler(); // Required for LVGL to refresh GUI
        update_label_number(get_turtle());
    }
}