
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "lvgl.h"
#include "lv_port_disp.h"

// #define PIN_CS 17
// #define PIN_DC 16
// #define PIN_RST 18
// #define PIN_BL 19
// #define PIN_SCK 2
// #define PIN_MOSI 3

// #define MY_DISP_HOR_RES 240
// #define MY_DISP_HOR_RES 280

int main()
{
    stdio_init_all();
    lv_init();
    lv_port_disp_init();

    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#ff0000 Re-color# #00ff00 words# #0000ff of a# label, align the lines to the center "
                              "and wrap long text automatically.");
    lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, -40);


    lv_obj_t * label2 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
    lv_obj_set_width(label2, 150);
    lv_label_set_text(label2, "It is a circularly scrolling text. ");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 40);
    while (true)
    {
        lv_timer_handler(); // Required for LVGL to refresh GUI
        lv_tick_inc(5);
        sleep_ms(5);
    }
}