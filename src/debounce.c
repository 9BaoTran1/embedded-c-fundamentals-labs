#include "debounce.h"

void debounce_init(debounce_t *button, bool initial_pressed, uint32_t threshold_ms)
{
    *button = (debounce_t){
        .stable = initial_pressed,
        .candidate = initial_pressed,
        .threshold_ms = threshold_ms
    };
}

bool debounce_sample(debounce_t *button, bool pressed, uint32_t now_ms)
{
    if (pressed != button->candidate) {
        button->candidate = pressed;
        button->since_ms = now_ms;
    }
    if (pressed == button->stable ||
        (uint32_t)(now_ms - button->since_ms) < button->threshold_ms) {
        return false;
    }
    button->stable = pressed;
    return true;
}
