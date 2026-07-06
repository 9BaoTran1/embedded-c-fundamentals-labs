#include <stdint.h>
#include <stdio.h>

#define CTRL_ENABLE_MASK      (1U << 0)
#define CTRL_INTERRUPT_MASK   (1U << 1)
#define CTRL_ERROR_MASK       (1U << 2)

static void print_register(const char *label, uint8_t value)
{
    printf("%s: 0x%02X\n", label, value);
}

int main(void)
{
    uint8_t control_register = 0U;

    control_register |= CTRL_ENABLE_MASK;
    control_register |= CTRL_INTERRUPT_MASK;
    print_register("after enable + interrupt", control_register);

    control_register &= (uint8_t)(~CTRL_INTERRUPT_MASK);
    print_register("after clear interrupt", control_register);

    control_register ^= CTRL_ERROR_MASK;
    print_register("after toggle error", control_register);

    if ((control_register & CTRL_ENABLE_MASK) != 0U) {
        puts("device is enabled");
    }

    return 0;
}
