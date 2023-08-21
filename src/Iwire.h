#ifndef IWIRE_H
#define IWIRE_H
#include "ports.h"
#include "../spiI2cuart/ssd1306.h"
#define TCCR2 *((volatile unsigned char *)0x45)
#define TCNT2 *((volatile unsigned char *)0x44)
#define TIFR *((volatile unsigned char *)0x58)

#define SREG *((volatile unsigned char *)0x5f)
#define I_ON SREG |= (1 << 7)
#define I_OFF SREG &= ~(1 << 7)

#define I_WIRE_BUS_PIN (1 << 0)
#define I_WIRE_BUS_RELEASE DDRC &= ~I_WIRE_BUS_PIN // using as input
#define I_WIRE_BUS_LOW DDRC |= I_WIRE_BUS_PIN      // using as output

// void DelayMicroSec(int micro)
// {
//     TCCR2 = (0 << 2) | (1 << 1) | (0 << 0); // 8 prescaler 1 tick == 1 microsec
//     TCNT2 = 255 - micro;
//     while (!((TIFR >> 6) & 1))
//         ;
//     TIFR |= (1 << 6);
// }
char ResetIwireBus()
{
    PORTC &= ~I_WIRE_BUS_PIN; // low
    I_WIRE_BUS_LOW;
    _delay_us(480);
    I_WIRE_BUS_RELEASE;
    _delay_us(70);
    char res = PINC & I_WIRE_BUS_PIN;
    _delay_us(410);
    return res;
}
void IwireWriteRomCmd(uint8_t ROM)
{
    for (char i = 0; i < 8; i++)
    {
        if ((ROM & 1) == 1)
        {
            I_WIRE_BUS_LOW;
            _delay_us(6);
            I_WIRE_BUS_RELEASE;
            _delay_us(64);
        }
        else
        {
            I_WIRE_BUS_LOW;
            _delay_us(60);
            I_WIRE_BUS_RELEASE;
            _delay_us(10);
        }
        ROM >>= 1;
    }
}
uint8_t IwireReadByte()
{
    uint8_t res = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        I_WIRE_BUS_LOW;
        _delay_us(6);
        I_WIRE_BUS_RELEASE;
        _delay_us(9);
        res |= (PINC & 1) << i; // cuz PC0
        _delay_us(55);
    }
    return res;
}

uint8_t IwireReadAddress(uint8_t arr[static 8])
{
    if (ResetIwireBus())
        return 0;

    IwireWriteRomCmd(0x33);

    for (uint8_t i = 0; i < 8; i++)
        arr[i] = IwireReadByte();

    return 1;
}

#endif