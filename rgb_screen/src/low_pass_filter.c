#include "low_pass_filter.h"

const static float alpha = 0.5;

unsigned int low_pass_filter(unsigned int input)
{
    static unsigned int filtered = 0;

    filtered = alpha * filtered + (1 - alpha) * input;

    return filtered;
}

unsigned int rate_limiter(unsigned int input)
{
    // Branhcless for fun. The disassembly does not contain any conditional branches
    static unsigned int filtered = 0;
    const unsigned int max_rise_per_call = 1;

    unsigned int value_rise_mask = -(input > filtered); // Either 0xFFFFFFFF or 0 , used as mask to false/true or take the results or discard them
    unsigned int rise = (input - filtered) & value_rise_mask;

    unsigned int limited_rise_mask = -(rise > max_rise_per_call);
    unsigned int limited_rise = (max_rise_per_call & limited_rise_mask) | (rise & ~limited_rise_mask);

    unsigned int filtered_rise = filtered + limited_rise;
    filtered = (filtered_rise & value_rise_mask) | (input & ~value_rise_mask);

    return filtered;
}