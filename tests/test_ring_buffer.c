#include "ring_buffer.h"

#include <assert.h>
#include <stdint.h>

int main(void)
{
    uint8_t storage[4];
    ring_buffer_t buffer;
    uint8_t value = 0U;

    assert(ring_buffer_init(&buffer, storage, 4U));
    assert(ring_buffer_is_empty(&buffer));
    assert(!ring_buffer_is_full(&buffer));

    assert(ring_buffer_push(&buffer, 10U));
    assert(ring_buffer_push(&buffer, 20U));
    assert(ring_buffer_push(&buffer, 30U));
    assert(ring_buffer_count(&buffer) == 3U);
    assert(ring_buffer_peek(&buffer, &value));
    assert(value == 10U);

    assert(ring_buffer_pop(&buffer, &value));
    assert(value == 10U);
    assert(ring_buffer_pop(&buffer, &value));
    assert(value == 20U);

    assert(ring_buffer_push(&buffer, 40U));
    assert(ring_buffer_push(&buffer, 50U));
    assert(ring_buffer_push(&buffer, 60U));
    assert(ring_buffer_is_full(&buffer));
    assert(!ring_buffer_push(&buffer, 70U));

    assert(ring_buffer_pop(&buffer, &value));
    assert(value == 30U);
    assert(ring_buffer_pop(&buffer, &value));
    assert(value == 40U);
    assert(ring_buffer_pop(&buffer, &value));
    assert(value == 50U);
    assert(ring_buffer_pop(&buffer, &value));
    assert(value == 60U);
    assert(ring_buffer_is_empty(&buffer));

    return 0;
}
