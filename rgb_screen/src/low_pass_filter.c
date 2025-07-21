#include "low_pass_filter.h"

const static float alpha = 0.5;

unsigned int  low_pass_filter(unsigned int input) {
    static unsigned int filtered = 0 ;

    filtered = alpha * filtered + (1 - alpha) * input;
    
    return filtered;
}