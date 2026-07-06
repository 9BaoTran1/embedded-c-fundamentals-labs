CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude -g
BUILD_DIR := build
TEST_DIR := $(BUILD_DIR)/tests
EXAMPLE_DIR := $(BUILD_DIR)/examples

COMMON_SRCS := src/ring_buffer.c src/uart_parser.c src/device_state_machine.c
TEST_TARGETS := \
	$(TEST_DIR)/test_ring_buffer \
	$(TEST_DIR)/test_uart_parser \
	$(TEST_DIR)/test_state_machine
EXAMPLE_TARGETS := \
	$(EXAMPLE_DIR)/bitwise_flags_demo \
	$(EXAMPLE_DIR)/volatile_polling_demo

.PHONY: all test examples clean

all: test examples

test: $(TEST_TARGETS)
	@for target in $(TEST_TARGETS); do ./$$target; done

examples: $(EXAMPLE_TARGETS)
	@for target in $(EXAMPLE_TARGETS); do ./$$target; done

$(TEST_DIR) $(EXAMPLE_DIR):
	@mkdir -p $@

$(TEST_DIR)/test_ring_buffer: tests/test_ring_buffer.c src/ring_buffer.c | $(TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_DIR)/test_uart_parser: tests/test_uart_parser.c src/uart_parser.c | $(TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_DIR)/test_state_machine: tests/test_state_machine.c src/device_state_machine.c | $(TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(EXAMPLE_DIR)/bitwise_flags_demo: examples/bitwise_flags_demo.c | $(EXAMPLE_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(EXAMPLE_DIR)/volatile_polling_demo: examples/volatile_polling_demo.c | $(EXAMPLE_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)
