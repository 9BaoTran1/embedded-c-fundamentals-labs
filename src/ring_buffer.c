#include "ring_buffer.h"

bool ring_buffer_init(ring_buffer_t *buffer, uint8_t *storage, size_t capacity)
{
    if (buffer == 0 || storage == 0 || capacity == 0U) {
        return false;
    }

    buffer->data = storage;
    buffer->capacity = capacity;
    ring_buffer_reset(buffer);
    return true;
}

void ring_buffer_reset(ring_buffer_t *buffer)
{
    if (buffer == 0) {
        return;
    }

    buffer->head = 0U;
    buffer->tail = 0U;
    buffer->count = 0U;
}

bool ring_buffer_push(ring_buffer_t *buffer, uint8_t value)
{
    if (buffer == 0 || ring_buffer_is_full(buffer)) {
        return false;
    }

    buffer->data[buffer->head] = value;
    buffer->head = (buffer->head + 1U) % buffer->capacity;
    buffer->count++;
    return true;
}

bool ring_buffer_pop(ring_buffer_t *buffer, uint8_t *value)
{
    if (buffer == 0 || value == 0 || ring_buffer_is_empty(buffer)) {
        return false;
    }

    *value = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1U) % buffer->capacity;
    buffer->count--;
    return true;
}

bool ring_buffer_peek(const ring_buffer_t *buffer, uint8_t *value)
{
    if (buffer == 0 || value == 0 || ring_buffer_is_empty(buffer)) {
        return false;
    }

    *value = buffer->data[buffer->tail];
    return true;
}

bool ring_buffer_is_empty(const ring_buffer_t *buffer)
{
    return buffer == 0 || buffer->count == 0U;
}

bool ring_buffer_is_full(const ring_buffer_t *buffer)
{
    return buffer != 0 && buffer->count == buffer->capacity;
}

size_t ring_buffer_count(const ring_buffer_t *buffer)
{
    return buffer == 0 ? 0U : buffer->count;
}
