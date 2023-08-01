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

#define PORTD *((volatile byte *)0x32) // output register of GPIO pins
#define DDRD *((volatile byte *)0x31)  // data direction register if 0-in pin, 1-out pin
#define PIND *((volatile byte *)0x30)  // input register read vals from gpio pin
#define PD ((P_PORT)0x32)

#endif