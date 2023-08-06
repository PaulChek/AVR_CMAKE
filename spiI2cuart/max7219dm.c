#include "max7219dm.h"

void MasterTransmittToRegisterMAX7219(byte reg_add, byte data)
{
    SPI_Master_Transmit(reg_add);
    SPI_Master_Transmit(data);
}

void LedM8x8_Init()
{
    CS_ON;
    MasterTransmittToRegisterMAX7219(INTENSITY_REG, 0x05);
    CS_OFF;

    CS_ON;
    MasterTransmittToRegisterMAX7219(SCAN_LIMIT_REG, 0x07);
    CS_OFF;

    CS_ON;
    MasterTransmittToRegisterMAX7219(SHUTDOWN_REG, 0x01);
    CS_OFF;

    CS_ON;
    MasterTransmittToRegisterMAX7219(DIPLAY_TEST_REG, 0x00);
    CS_OFF;
}

void LedM8x8_Clear()
{
    for (byte i = DIGIT0_REG; i <= 8; i++)
    {
        CS_ON;
        MasterTransmittToRegisterMAX7219(i, 0);
        CS_OFF;
    }
}

void LedM8x8_Set()
{
    for (byte i = DIGIT0_REG; i <= 8; i++)
    {
        CS_ON;
        MasterTransmittToRegisterMAX7219(i, 0xFF);
        CS_OFF;
    }
}
void LedM8x8_Show(byte * map)
{
    for (byte i = DIGIT0_REG; i <= 8; i++)
    {
        CS_ON;
        MasterTransmittToRegisterMAX7219(i, *map);
        CS_OFF;
        map++;
    }
}