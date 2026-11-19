# GPIO button sampling on a periodic task

A mechanical switch can briefly alternate between open and closed. With a pull-up and a switch to ground, a low pin means pressed. A useful input to a state machine is one press event and one release event per actuation.

## Reproduce the experiment

Run `make test` from the repository root. Open `tests/test_debounce.c` and change the final press sample from 19 ms to 18 ms. Predict the failed assertion, run the test, and restore 19 ms. The last bounce ended at 9 ms and the configured threshold is 10 ms.

| Time (ms) | Raw input | Accepted event |
| ---: | --- | --- |
| 3 | pressed | — |
| 8 | released | — |
| 9 | pressed | — |
| 18 | pressed | — |
| 19 | pressed | press |
| 40 | pressed | — |

## Porting the lab to an STM32 board

1. Read the board schematic for the button pin and polarity. Enable the GPIO clock and configure the pin as input with the pull arrangement required by the board. Normalize the register sample, e.g. `bool pressed = (gpio->IDR & button_mask) == 0u;` for an active-low switch. Initialize the filter with the first observed level to suppress a boot-time event.
2. Give one task ownership of the filter. Inspect a single input snapshot on each periodic wake and call `debounce_sample`. Example design values are a 2 ms sample interval and a 10 ms stability threshold. Select values for the actual switch and available tick resolution. Deliver a press or release only when the function returns true.
3. Supply a monotonic unsigned 32-bit counter in milliseconds. Under FreeRTOS, schedule against an absolute wake time using the periodic delay API in the installed kernel. A raw RTOS tick is only one millisecond at 1 kHz. For another rate, use a suitable millisecond timebase or adapt all durations to the same tick unit. Verify that the requested sampling period spans at least one tick. The unsigned elapsed-time subtraction tolerates rollover while the pending interval remains shorter than one full counter cycle.
4. With regular sampling this rejects changes shorter than the threshold as observed at sample instants. A long pause leaves the input unobserved. A board experiment should log late samples and either restart the candidate interval after a missed deadline or justify the tolerated gap. Measure raw edges and accepted events on a logic analyzer before selecting a production threshold.

## Luyện trả lời phỏng vấn

- **Tại sao đọc thanh ghi GPIO cần volatile?** Ngoại vi có thể đổi giá trị giữa hai lần đọc. Sau khi đọc một lần, tách bit từ bản sao cục bộ. Đồng bộ dữ liệu giữa ISR và task là một vấn đề riêng.
- **Tại sao mốc 18 ms chưa báo nhấn?** Mốc bắt đầu quan sát ổn định gần nhất là 9 ms. Tự vẽ thêm một lần dội ở 17 ms và tính lại thời điểm có thể phát sự kiện.
- **Vì sao phép trừ còn đúng khi bộ đếm quay vòng?** Từ UINT32_MAX − 4 đến 5 là 10 bước của bộ đếm 32 bit. Đọc test và giải thích giới hạn một vòng đếm.
- **Khi nào chọn ngắt thay cho polling?** So sánh thời gian đáp ứng, đánh thức thiết bị và dội tiếp điểm. Nếu dùng EXTI để đánh thức task, xác minh mức ưu tiên NVIC và điều kiện gọi API FromISR. Để task xử lý lọc và đo số lần đánh thức khi thử trên board.
- **Nếu nhà tuyển dụng hỏi bằng chứng?** Chạy test, giải thích một assertion, rồi phân biệt kết quả trên host với phép đo cần thu trên STM32. Trình bày kinh nghiệm phần cứng qua dự án robot có sẵn.

## Reading map

PDF page numbers below are one-based file pages in the FastBit Embedded Brain Academy material.

| Local reading | Pages | Practice |
| --- | --- | --- |
| Embedded-C.pdf | 218–219, 475–476 | Extract an input bit and explain a volatile read. |
| Embedded_driver.pdf | 55, 76, 143–144 | Sketch the GPIO input, pull and button path on the target board. |
| Emebdded_system_programming_on_CortexM3M4.pdf | 128–129, 242–245 | Trace peripheral interrupt delivery and explain the timer timebase. |
| RTOS.pdf | 265, 279, 312–315 | Explain ISR API constraints and compare relative versus periodic task delay. |

The executable lab runs on the host. STM32 register configuration, FreeRTOS timing, and physical switch behavior are board follow-up exercises.
