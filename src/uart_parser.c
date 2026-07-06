#include "uart_parser.h"

#include <string.h>

void uart_parser_init(uart_parser_t *parser)
{
    if (parser == 0) {
        return;
    }

    memset(parser->line, 0, sizeof(parser->line));
    parser->length = 0U;
    parser->overflowed = false;
}

uart_parse_result_t uart_parser_feed(
    uart_parser_t *parser,
    uint8_t byte,
    char *out_line,
    size_t out_capacity
)
{
    if (parser == 0 || out_line == 0 || out_capacity == 0U) {
        return UART_PARSE_OVERFLOW;
    }

    if (byte == '\r') {
        return UART_PARSE_NO_LINE;
    }

    if (byte == '\n') {
        if (parser->overflowed) {
            uart_parser_init(parser);
            return UART_PARSE_OVERFLOW;
        }

        if (parser->length >= out_capacity) {
            uart_parser_init(parser);
            return UART_PARSE_OVERFLOW;
        }

        memcpy(out_line, parser->line, parser->length);
        out_line[parser->length] = '\0';
        uart_parser_init(parser);
        return UART_PARSE_LINE_READY;
    }

    if (parser->length >= (UART_PARSER_MAX_LINE_LEN - 1U)) {
        parser->overflowed = true;
        return UART_PARSE_NO_LINE;
    }

    parser->line[parser->length] = (char)byte;
    parser->length++;
    parser->line[parser->length] = '\0';
    return UART_PARSE_NO_LINE;
}
