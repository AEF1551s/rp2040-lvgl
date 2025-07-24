#include "motor.h"

static const uint MOTOR_PIN = 1;
static const uint PWM_WRAP = CLAMP_HIGH - CLAMP_LOW;
static const uint TURTLE_OFFSET = CLAMP_LOW;

static void on_pwm_wrap();

static void on_pwm_wrap()
{

    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(MOTOR_PIN));

    // Square the fade value to make the LED's brightness appear more linear
    // Note this range matches with the wrap value
    pwm_set_gpio_level(MOTOR_PIN, get_turtle() - TURTLE_OFFSET);
}

void motor_init()
{
    // gpio_init(MOTOR_PIN);
    // gpio_set_dir(MOTOR_PIN, GPIO_OUT);
    // gpio_put(MOTOR_PIN, 0);

    // Tell the LED pin that the PWM is in charge of its value.
    gpio_set_function(MOTOR_PIN, GPIO_FUNC_PWM);
    // Figure out which slice we just connected to the LED pin
    uint slice_num = pwm_gpio_to_slice_num(MOTOR_PIN);

    // Mask our slice's IRQ output into the PWM block's single interrupt line,
    // and register our interrupt handler
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_DEFAULT_IRQ_NUM(), on_pwm_wrap);
    irq_set_enabled(PWM_DEFAULT_IRQ_NUM(), true);

    // Get some sensible defaults for the slice configuration. By default, the
    // counter is allowed to wrap over its maximum range (0 to 2**16-1)
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, PWM_WRAP);
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, 1.f);
    // pwm_config_set_clkdiv(&config, 0);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);
}