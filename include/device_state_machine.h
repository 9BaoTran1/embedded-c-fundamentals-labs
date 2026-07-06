#ifndef DEVICE_STATE_MACHINE_H
#define DEVICE_STATE_MACHINE_H

typedef enum {
    DEVICE_STATE_IDLE = 0,
    DEVICE_STATE_ARMED,
    DEVICE_STATE_RUNNING,
    DEVICE_STATE_FAULT
} device_state_t;

typedef enum {
    DEVICE_EVENT_POWER_ON = 0,
    DEVICE_EVENT_ARM_COMMAND,
    DEVICE_EVENT_START_COMMAND,
    DEVICE_EVENT_STOP_COMMAND,
    DEVICE_EVENT_FAULT_DETECTED,
    DEVICE_EVENT_RESET_FAULT
} device_event_t;

typedef struct {
    device_state_t current_state;
} device_state_machine_t;

void device_state_machine_init(device_state_machine_t *machine);
void device_state_machine_handle_event(
    device_state_machine_t *machine,
    device_event_t event
);
const char *device_state_name(device_state_t state);

#endif
