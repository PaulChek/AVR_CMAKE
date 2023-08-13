#include "spi.h"

void SPI_Master_Init()
{
    /* Set MOSI and SCK output*/
   // *((volatile byte *)(0x38)) |= (1 << 4); // SS high on the master mode PORTB
    DDR_SPI = (1 << MOSI) | (1 << SCK)|(1<<4);
    /* Enable SPI, Master, set clock rate fosc/4 */
    SPCR = (1 << SPE) | (1 << MSTR) | (0 << CPOL) | (0 << CPOH) | (0 << SPR0);
}

void SPI_Master_Transmit(unsigned char data)
{
    *((volatile byte *)0x35) |=(1<<3);
    // start transmission by placing data in shift reg
    char x = '\0';
    SPDR = data;
    // wait for transmission complete(1)
    while (!(SPSR & (1 << SPIF)))
        ;
    x = SPDR; // flashing SPDR
   *((volatile byte *)0x35) &=~(1<<3);
}