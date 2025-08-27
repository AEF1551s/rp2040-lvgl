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

static const uint ADC_CHANNEL = 1;
static const uint TIMER_NUM = 0;
static const uint ALARM_NUM = 2;
static const uint ALARM_IRQ = 2;
static const uint32_t PERIOD_MS = 1000; // Set battery reading interval.

static volatile uint16_t adc_value_batt = 0;
static volatile uint16_t adc_value_f_batt = 0;

static void write_batt_proc()
{
    // TODO: implement average over certain period, period = PERIOD_MS, do conversion from ADC to 0-100
    adc_value_f_batt = adc_value_batt/40;
}

static void batt_read_irq(void)
{
    static uint64_t target = 0;
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);

    target = timer_hw->timerawl + (PERIOD_MS * 1000);
    timer_hw->alarm[ALARM_NUM] = (uint32_t)target;

    adc_select_input(ADC_CHANNEL);
    adc_value_batt = adc_read(); // raw batt level

    printf("%u\n", adc_value_batt); // Set source based on battery level
    write_batt_proc();

}

static void batt_alarm_ms_init()
{
    // Enable the interrupt for our alarm (the timer outputs 4 alarm irqs: 0-3)
    hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM);

    // Set irq handler for alarm irq
    irq_set_exclusive_handler(ALARM_IRQ, batt_read_irq);

    // Enable the alarm irq
    irq_set_enabled(ALARM_IRQ, true);

    // Set initial target
    uint64_t target = timer_hw->timerawl + (PERIOD_MS * 1000);
    timer_hw->alarm[ALARM_NUM] = (uint32_t)target;

}

void battery_init(lv_obj_t *screen)
{
    screen = lv_scr_act();

    battery = lv_img_create(screen);
    lv_obj_align(battery, LV_ALIGN_TOP_LEFT, battery_x, battery_y);
    lv_timer_create(update_battery, BATT_UPDATE_MS, NULL);

    // Draw the battery first
    update_battery(0);

    adc_init();
    adc_gpio_init(BATTERY_ADC_PIN);

    batt_alarm_ms_init();
    // alarm_irq();
}

void update_battery()
{
    printf("%d\n", (int)adc_value_f_batt); // Set source based on battery level
    // TODO: battery status enum and battery get function
    unsigned int level = adc_value_f_batt;

    if (level >= 85)
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

    // level += 10;
    // level %= 101;
}
