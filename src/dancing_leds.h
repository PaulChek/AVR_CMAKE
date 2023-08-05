#ifndef DANCING_H
#define DANCING_H
#include "ports.h"
#include <util/delay.h>

void my_delay(byte t)
{
    while (t-- && PIND<<6)
        _delay_ms(1);
    // __builtin_avr_delay_cycles(F_CPU/1000);//1ms
}

void dance_leds(byte start_delay_time)
{

    PORTC = 1;
    while (my_delay(start_delay_time), PORTC <<= 1)
        ;


    PORTC = 1 << 7;
    while (my_delay(start_delay_time), PORTC >>= 1);
   
}

#endif