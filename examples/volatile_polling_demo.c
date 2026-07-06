#include <stdint.h>
#include <stdio.h>

typedef struct {
    volatile uint32_t status;
    volatile uint32_t data;
} mock_uart_registers_t;

#define UART_STATUS_RX_READY_MASK  (1UL << 0)

static uint32_t uart_read_when_ready(mock_uart_registers_t *uart)
{
    while ((uart->status & UART_STATUS_RX_READY_MASK) == 0UL) {
        /* Busy wait to simulate polling a hardware register. */
    }

    return uart->data;
}

int main(void)
{
    mock_uart_registers_t uart = {0};

    uart.data = 0x41UL;
    uart.status |= UART_STATUS_RX_READY_MASK;

    printf("read value: 0x%02lX\n", (unsigned long)uart_read_when_ready(&uart));
    return 0;
}
