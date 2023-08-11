#ifndef TIMER0_H
#define TIMER0_H
#include <stdint.h>
#include <avr/interrupt.h>
/**
 * TCNT0 0x52 Timer/counter 8 bits
 *
 */

#define TCCR0 *((unsigned char *)0x53) // Timer/Counter Control Register [7 6 5 4 3 CS02 CS01 CS00] 0b101 for /1024

#define TCNT0 *((unsigned char *)0x52) // 8 bit reg for counting cycles of mcu [255 - needed cycles]
#define TIFR *((unsigned char *)0x58)  // TIMER interupt flags
#define TIMSK *((unsigned char *)0x59) // timers mask interrupts
#define SREG *((unsigned char *)0x5F)  // AVR Status Register

static int16_t counter = 0;

ISR(TIMER0_OVF_vect)
{ // interrupt vector
    counter--;
    // TIFR = 1; // it clears flag to zero))) auto in Interup services
    TCNT0 = 256 - 78;
}

void setupTimer0(int ms10)
{
    counter = ms10;
    TCCR0 = 0b101;     // freq/1024
    TCNT0 = 256 - 78;  // almost 10 ms 256 -78
    TIFR = 1;          // clear flag
    TIMSK |= (1 << 0); // enable interrupts on overflow timer0 if SREG i-bit is one
    SREG |= (1 << 7);  // sei() enable global interrupts
}
int16_t timer0()
{
    return counter;
}
#endif