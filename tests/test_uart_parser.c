#include "uart_parser.h"

#include <assert.h>
#include <stddef.h>

static void feed_string(uart_parser_t *parser, const char *text, char *output)
{
    size_t index = 0U;
    while (text[index] != '\0') {
        uart_parse_result_t result = uart_parser_feed(
            parser,
            (unsigned char)text[index],
            output,
            UART_PARSER_MAX_LINE_LEN
        );

        if (text[index] == '\n') {
            assert(result == UART_PARSE_LINE_READY);
        } else {
            assert(result == UART_PARSE_NO_LINE);
        }
        index++;
    }
}

int main(void)
{
    uart_parser_t parser;
    char output[UART_PARSER_MAX_LINE_LEN];
    uart_parse_result_t result;

    uart_parser_init(&parser);
    feed_string(&parser, "G1 X10 Y20\n", output);
    assert(output[0] == 'G');
    assert(output[1] == '1');

    uart_parser_init(&parser);
    result = uart_parser_feed(&parser, 'A', output, sizeof(output));
    assert(result == UART_PARSE_NO_LINE);
    result = uart_parser_feed(&parser, '\r', output, sizeof(output));
    assert(result == UART_PARSE_NO_LINE);
    result = uart_parser_feed(&parser, '\n', output, sizeof(output));
    assert(result == UART_PARSE_LINE_READY);
    assert(output[0] == 'A');
    assert(output[1] == '\0');

    uart_parser_init(&parser);
    for (size_t index = 0U; index < UART_PARSER_MAX_LINE_LEN; ++index) {
        (void)uart_parser_feed(&parser, 'Z', output, sizeof(output));
    }
    result = uart_parser_feed(&parser, '\n', output, sizeof(output));
    assert(result == UART_PARSE_OVERFLOW);

    return 0;
}
