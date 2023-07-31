#define F_CPU 8000000UL
#include "ports.h"
#include <util/delay.h>

int main()
{
    DDRD = 1 << 7 | 1 << 6;
    while (1)
    {
        _delay_ms(100);
        PORTD ^= 1 << 7 | 1 << 6;
    }

    return 0;
}
