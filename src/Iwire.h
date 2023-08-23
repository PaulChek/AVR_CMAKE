#ifndef IWIRE_H
#define IWIRE_H
#include "ports.h"
#include "../spiI2cuart/ssd1306.h"
#define TCCR2 *((volatile unsigned char *)0x45)
#define TCNT2 *((volatile unsigned char *)0x44)
#define TIFR *((volatile unsigned char *)0x58)

#define READ_ROM 0x33
#define CONVERT_T 0x44 // ds18b20
#define MATCH_ROM 0x55
#define READ_SCRATCHPAD 0xBE  // ds18b20
#define WRITE_SCRATCHPAD 0x4E // ds18b20

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

    IwireWriteRomCmd(READ_ROM);

    for (uint8_t i = 0; i < 8; i++)
        arr[i] = IwireReadByte();

    return 1;
}
// ds18b20
char *ConvertNumToString(uint8_t mb, uint8_t lb);
char *DS18B20GetTemperature(uint8_t device_address[static 8])
{
    // I
    if (ResetIwireBus())
        return 0;
    IwireWriteRomCmd(MATCH_ROM); // match rom
    for (uint8_t i = 0; i < 8; i++)
    {
        IwireWriteRomCmd(device_address[i]);
    }
    IwireWriteRomCmd(CONVERT_T);
    // II
    _delay_ms(94);
    ResetIwireBus();
    IwireWriteRomCmd(MATCH_ROM); // match rom
    for (uint8_t i = 0; i < 8; i++)
        IwireWriteRomCmd(device_address[i]);

    uint8_t temp[9] = {0};
    IwireWriteRomCmd(READ_SCRATCHPAD); // read scratchpad
    for (uint8_t i = 0; i < 9; i++)
        temp[i] = IwireReadByte();

    return ConvertNumToString(temp[1], temp[0]);
}

char *ConvertNumToString(uint8_t mb, uint8_t lb)
{
    static char res[6] = {[3] = '.', '0', '\0'};
    static char *res_p = res;
    
    if ((lb >> 3) & 1 == 1)
        res[4] = '5';
    else
        res[4] = '0';

    uint16_t val = (mb << 8) | lb;
    val = (val << 5) >> 9; // removing sign
    res_p += 2;
    while (val)
    {
        *res_p-- = (val % 10) + '0';
        val /= 10;
    }
    return res_p + 1;
}

uint8_t SetDS18B20Resolution(uint8_t device_adr[static 8], uint8_t data[static 3])
{ // TH,TL, (Conf reg)Resolution
    if (ResetIwireBus())
        return 0;
    IwireWriteRomCmd(MATCH_ROM);
    for (uint8_t i = 0; i < 8; i++)
        IwireWriteRomCmd(device_adr[i]);
    // II

    IwireWriteRomCmd(WRITE_SCRATCHPAD);
    for (uint8_t i = 0; i < 3; i++)
        IwireWriteRomCmd(data[i]);
    return 1;
}
#endif