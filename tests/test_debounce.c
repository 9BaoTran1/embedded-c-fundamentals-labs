#include "debounce.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    debounce_t b;
    debounce_init(&b, false, 10);
    assert(!debounce_sample(&b, true, 3));
    assert(!debounce_sample(&b, false, 8));  /* Contact bounced back. */
    assert(!debounce_sample(&b, true, 9));
    assert(!debounce_sample(&b, true, 18));
    assert(debounce_sample(&b, true, 19) && b.stable);
    assert(!debounce_sample(&b, true, 40));  /* A hold produces one press. */
    assert(!debounce_sample(&b, false, 44));
    assert(!debounce_sample(&b, true, 46));
    assert(!debounce_sample(&b, false, 48));
    assert(debounce_sample(&b, false, 58) && !b.stable);

    debounce_init(&b, true, 10);
    assert(!debounce_sample(&b, true, UINT32_MAX - 5));
    assert(!debounce_sample(&b, false, UINT32_MAX - 4));
    assert(!debounce_sample(&b, false, 4));
    assert(debounce_sample(&b, false, 5) && !b.stable);

    debounce_init(&b, false, 0);
    assert(debounce_sample(&b, true, 0) && b.stable);
    assert(!debounce_sample(&b, true, 0));
    puts("PASS debounce: bounce, hold, release, startup, rollover, zero threshold");
    return 0;
}
