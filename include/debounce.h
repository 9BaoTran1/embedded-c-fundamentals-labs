#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool stable;
    bool candidate;
    uint32_t since_ms;
    uint32_t threshold_ms;
} debounce_t;

/* One sampling task owns the state. Pass normalized pressed/released levels. */
void debounce_init(debounce_t *button, bool initial_pressed, uint32_t threshold_ms);
/* Returns true once per accepted change. Read button->stable for the new state. */
bool debounce_sample(debounce_t *button, bool pressed, uint32_t now_ms);

#endif
