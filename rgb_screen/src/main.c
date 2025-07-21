
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "turtle.h"
#include "motor.h"

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
    }
}