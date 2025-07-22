#include "lv_screen.h"

static lv_obj_t *screen = NULL;
static lv_obj_t *label = NULL;

static char buf[10];

const static uint TIMER_NUM = 0;
const static uint ALARM_NUM = 1;
const static uint ALARM_IRQ = 1;
const static uint32_t PERIOD_MS = 1;

const static unsigned int Y_OFFSET = 20;

const static unsigned int SPEED_UPDATE_MS = 50;

void create_centered_number_label()
{
    // Create a label
    // label = lv_label_create(parent);
    label = lv_label_create(screen);

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

void update_speed()
{
    char buf[5];
    snprintf(buf, sizeof(buf), "%u", get_turtle());
    lv_label_set_text(label, buf);
    lv_obj_center(label); // recenter in case width changes (e.g. 1 → 10)
}

static void lv_tick_irq(void)
{
    static uint64_t target = 0;
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);
    target = timer_hw->timerawl + (PERIOD_MS * 1000);
    timer_hw->alarm[ALARM_NUM] = (uint32_t)target;

    lv_tick_inc(1);
}
static void lv_tick_init()
{
    // Enable the interrupt for our alarm (the timer outputs 4 alarm irqs)
    hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM);
    // Set irq handler for alarm irq
    irq_set_exclusive_handler(ALARM_IRQ, lv_tick_irq);
    // Enable the alarm irq
    irq_set_enabled(ALARM_IRQ, true);

    // Alarm is only 32 bits so if trying to delay more
    // than that need to be careful and keep track of the upper
    // bits
    uint64_t target = timer_hw->timerawl + (PERIOD_MS * 1000);

    // Write the lower 32 bits of the target time to the alarm which
    // will arm it
    timer_hw->alarm[ALARM_NUM] = (uint32_t)target;
}

void speed_init()
{
    create_centered_number_label();
    lv_timer_create(update_speed, SPEED_UPDATE_MS, NULL);
}

// Initialize every object on screen, timer for updating them.
void screen_init()
{
    lv_init();
    lv_port_disp_init();
    lv_tick_init();

    screen = lv_scr_act();

    battery_init(screen);
    speed_init();
}