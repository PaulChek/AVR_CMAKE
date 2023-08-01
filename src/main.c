#define F_CPU 8000000UL
#include "ports.h"
#include <util/delay.h>

int main()
{
    DDRD = 1<<7| 1 << 6;

    while (1)
    {
        PD->N7 ^= 1;
        _delay_ms(150);
        PD->N6 ^= 1;
    }

    return 0;
}
