#ifndef UART_PARSER_H
#define UART_PARSER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define UART_PARSER_MAX_LINE_LEN 64U

typedef enum {
    UART_PARSE_NO_LINE = 0,
    UART_PARSE_LINE_READY,
    UART_PARSE_OVERFLOW
} uart_parse_result_t;

typedef struct {
    char line[UART_PARSER_MAX_LINE_LEN];
    size_t length;
    bool overflowed;
} uart_parser_t;

void uart_parser_init(uart_parser_t *parser);
uart_parse_result_t uart_parser_feed(
    uart_parser_t *parser,
    uint8_t byte,
    char *out_line,
    size_t out_capacity
);

#endif
