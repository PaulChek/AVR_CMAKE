#ifndef PORTS_H
#define PORTS_H

typedef unsigned char byte;
#define PORTD *((volatile byte *)0x32)
#define DDRD *((volatile byte *)0x31)


#endif