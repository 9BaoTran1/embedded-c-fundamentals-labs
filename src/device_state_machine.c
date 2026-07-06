#include "device_state_machine.h"

void device_state_machine_init(device_state_machine_t *machine)
{
    if (machine == 0) {
        return;
    }

    machine->current_state = DEVICE_STATE_IDLE;
}

void device_state_machine_handle_event(
    device_state_machine_t *machine,
    device_event_t event
)
{
    if (machine == 0) {
        return;
    }

    switch (machine->current_state) {
    case DEVICE_STATE_IDLE:
        if (event == DEVICE_EVENT_POWER_ON || event == DEVICE_EVENT_ARM_COMMAND) {
            machine->current_state = DEVICE_STATE_ARMED;
        } else if (event == DEVICE_EVENT_FAULT_DETECTED) {
            machine->current_state = DEVICE_STATE_FAULT;
        }
        break;

    case DEVICE_STATE_ARMED:
        if (event == DEVICE_EVENT_START_COMMAND) {
            machine->current_state = DEVICE_STATE_RUNNING;
        } else if (event == DEVICE_EVENT_STOP_COMMAND) {
            machine->current_state = DEVICE_STATE_IDLE;
        } else if (event == DEVICE_EVENT_FAULT_DETECTED) {
            machine->current_state = DEVICE_STATE_FAULT;
        }
        break;

    case DEVICE_STATE_RUNNING:
        if (event == DEVICE_EVENT_STOP_COMMAND) {
            machine->current_state = DEVICE_STATE_IDLE;
        } else if (event == DEVICE_EVENT_FAULT_DETECTED) {
            machine->current_state = DEVICE_STATE_FAULT;
        }
        break;

    case DEVICE_STATE_FAULT:
        if (event == DEVICE_EVENT_RESET_FAULT) {
            machine->current_state = DEVICE_STATE_IDLE;
        }
        break;

    default:
        machine->current_state = DEVICE_STATE_FAULT;
        break;
    }
}

const char *device_state_name(device_state_t state)
{
    switch (state) {
    case DEVICE_STATE_IDLE:
        return "IDLE";
    case DEVICE_STATE_ARMED:
        return "ARMED";
    case DEVICE_STATE_RUNNING:
        return "RUNNING";
    case DEVICE_STATE_FAULT:
        return "FAULT";
    default:
        return "UNKNOWN";
    }
}
