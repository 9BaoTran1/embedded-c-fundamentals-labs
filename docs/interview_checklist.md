# Interview Checklist

Use this repo to practice explaining core embedded ideas out loud.

## Ring Buffer

- Why use a ring buffer for UART RX data?
- What is the difference between `head`, `tail`, and `count`?
- How do you detect full vs empty?
- What changes if push/pop happen in interrupt context?

## UART Parser

- Why parse one byte at a time?
- Why ignore `\r` but treat `\n` as line completion?
- What should happen on buffer overflow?
- When would you switch from line parsing to frame parsing?

## State Machine

- Why use states instead of many boolean flags?
- Which events are valid in each state?
- What happens if an invalid event arrives?
- How would you add a timeout-driven transition?

## Bitwise Operations

- How do you set, clear, toggle, and check a bit?
- Why are bit masks common in register programming?
- Why cast after `~MASK` on small integer types?

## Volatile

- Why are hardware registers often declared `volatile`?
- Why is `volatile` not a replacement for synchronization?
- Where is polling acceptable, and when is interrupt-driven code better?
