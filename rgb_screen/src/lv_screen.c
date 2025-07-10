#include "lv_screen.h"

static lv_obj_t *label;

void create_centered_number_label()
{
    // Create a label
    // label = lv_label_create(parent);
    label = lv_label_create(lv_scr_act());

    // Set initial text (0–99)
    char buf[5]; // Enough for "99\0"
    snprintf(buf, sizeof(buf), "%u", 0);
    lv_label_set_text(label, buf);

    // Create style with larger font
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, &lv_font_montserrat_48); // ← larger font

    // Apply style to label
    lv_obj_add_style(label, &style, 0);

    // Center the label on the screen
    lv_obj_center(label);
}

void update_label_number(unsigned int number)
{
    char buf[5];
    snprintf(buf, sizeof(buf), "%u", number);
    lv_label_set_text(label, buf);
    lv_obj_center(label); // recenter in case width changes (e.g. 1 → 10)
}


// Timer callback function
bool lv_tick(repeating_timer_t *rt) {
    lv_tick_inc(1);
    return true;  // return true to keep repeating
}

void screen_init(){
    lv_init();
    lv_port_disp_init();

    create_centered_number_label();
    update_label_number(10);

    static repeating_timer_t timer;
    add_repeating_timer_us(-1000, lv_tick, NULL, &timer);
}