#include "gpio_indicator.h"

volatile bool indicator_left_flag = false;
volatile bool indicator_right_flag = true;
//  TODO: implement gpio irq for button press