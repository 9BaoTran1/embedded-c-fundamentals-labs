# Embedded C Fundamentals Labs

Practice repository for core embedded C topics that appear often in fresher
firmware interviews.

This repo is intentionally small and focused. The goal is to build confidence in
the fundamentals behind MCU firmware work:

- bitwise operations and register flags
- ring buffer design
- UART line parsing
- finite state machines
- `volatile` and polling concepts

## Repository Layout

| Path | Purpose |
| --- | --- |
| `include/` | Public headers for reusable modules |
| `src/` | Core C implementations |
| `tests/` | Small test programs using `assert` |
| `examples/` | Standalone demos for interview-style concepts |
| `docs/` | Study notes and interview checklist |

## Labs

1. `examples/bitwise_flags_demo.c`
   Register masks, set/clear/toggle/check operations.

2. `src/ring_buffer.c`
   Fixed-size byte ring buffer used in embedded serial workflows.

3. `src/uart_parser.c`
   Byte-by-byte UART line parser with newline detection and overflow handling.

4. `src/device_state_machine.c`
   Small finite state machine for a device with `IDLE`, `ARMED`, `RUNNING`, and
   `FAULT` states.

5. `examples/volatile_polling_demo.c`
   Short example showing why hardware-facing registers are commonly declared
   `volatile`.

6. [GPIO button debounce lab](docs/gpio-debounce.md)
   Follow an active-low input through a periodic sampler. Run the C tests for contact bounce, held buttons, release and 32-bit counter rollover. Includes STM32/FreeRTOS porting notes and interview exercises.

## Build and Run

This repository builds with `gcc` and `make`.

From WSL or Linux:

```bash
make
make test
make examples
```

Clean build artifacts:

```bash
make clean
```

## Why This Repo Matters

For fresher embedded interviews, project experience helps, but interviewers also
check whether the basics are solid. This repo is meant to strengthen the gap
between "I used Arduino/ESP32 in projects" and "I can explain and implement core
firmware building blocks clearly."

## Suggested Study Order

1. Bitwise flags
2. Ring buffer
3. UART parser
4. State machine
5. Volatile and polling

## Next Extensions

- add checksum validation for UART frames
- add a timer-driven state machine example
- add a command parser with enum-based dispatch
