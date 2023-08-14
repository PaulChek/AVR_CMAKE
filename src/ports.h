#ifndef PORTS_H
#define PORTS_H

typedef unsigned char byte;
// struct for GPIO ports
typedef volatile struct PORT_S
{
    byte N0 : 1;
    byte N1 : 1;
    byte N2 : 1;
    byte N3 : 1;
    byte N4 : 1;
    byte N5 : 1;
    byte N6 : 1;
    byte N7 : 1;
} PORT, *P_PORT;
// A
#define PORTA *((volatile byte *)0x3b)
#define DDRA *((volatile byte *)0x3a)
#define PINA *((volatile byte *)0x39)
// B
#define PORTB *((volatile byte *)0x38)
// D
#define PORTD *((volatile byte *)0x32) // output register of GPIO pins
#define DDRD *((volatile byte *)0x31)  // data direction register if 0-in pin, 1-out pin
#define PIND *((volatile byte *)0x30)  // input register read vals from gpio pin
// C
#define PORTC *((volatile byte *)0x35)
#define DDRC *((volatile byte *)0x34)
#define PINC *((volatile byte *)0x33)

#define PD ((P_PORT)0x32)

#endif