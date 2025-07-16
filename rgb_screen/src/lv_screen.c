#include "lv_screen.h"

static lv_obj_t *label;
static char buf[10];

const static uint SCREEN_TIMER_NUM = 0;
const static uint SCREEN_ALARM_NUM = 1;
const static uint SCREEN_ALARM_IRQ = 1;
const static uint32_t SCREEN_PERIOD_MS = 20;

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

static void lv_tick_irq(void)
{
    static uint64_t target = 0;
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << SCREEN_ALARM_NUM);
    target = timer_hw->timerawl + (SCREEN_PERIOD_MS * 1000);
    timer_hw->alarm[SCREEN_ALARM_NUM] = (uint32_t)target;

    lv_tick_inc(1);
}
static void alarm_ms_init()
{
    // Enable the interrupt for our alarm (the timer outputs 4 alarm irqs)
    hw_set_bits(&timer_hw->inte, 1u << SCREEN_ALARM_NUM);
    // Set irq handler for alarm irq
    irq_set_exclusive_handler(SCREEN_ALARM_IRQ, lv_tick_irq);
    // Enable the alarm irq
    irq_set_enabled(SCREEN_ALARM_IRQ, true);

    // Alarm is only 32 bits so if trying to delay more
    // than that need to be careful and keep track of the upper
    // bits
    uint64_t target = timer_hw->timerawl + (SCREEN_PERIOD_MS * 1000);

    // Write the lower 32 bits of the target time to the alarm which
    // will arm it
    timer_hw->alarm[SCREEN_ALARM_NUM] = (uint32_t)target;
}

void screen_init()
{
    lv_init();
    lv_port_disp_init();
    alarm_ms_init();

    create_centered_number_label();
    update_label_number(10);
}