#include "device_state_machine.h"

#include <assert.h>

int main(void)
{
    device_state_machine_t machine;

    device_state_machine_init(&machine);
    assert(machine.current_state == DEVICE_STATE_IDLE);

    device_state_machine_handle_event(&machine, DEVICE_EVENT_ARM_COMMAND);
    assert(machine.current_state == DEVICE_STATE_ARMED);

    device_state_machine_handle_event(&machine, DEVICE_EVENT_START_COMMAND);
    assert(machine.current_state == DEVICE_STATE_RUNNING);

    device_state_machine_handle_event(&machine, DEVICE_EVENT_FAULT_DETECTED);
    assert(machine.current_state == DEVICE_STATE_FAULT);

    device_state_machine_handle_event(&machine, DEVICE_EVENT_RESET_FAULT);
    assert(machine.current_state == DEVICE_STATE_IDLE);

    device_state_machine_handle_event(&machine, DEVICE_EVENT_START_COMMAND);
    assert(machine.current_state == DEVICE_STATE_IDLE);

    return 0;
}
