#include "spi.h"

void SPI_Master_Init()
{
    /* Set MOSI and SCK output*/
    DDR_SPI = (1 << MOSI) | (1 << SCK);
    /* Enable SPI, Master, set clock rate fosc/4 */
    SPCR = (1 << SPE) | (1 << MSTR) | (0 << SPR0);
}

void SPI_Master_Transmit(unsigned char data)
{
    // start transmission by placing data in shift reg
    char x = '\0';
    SPDR = data;
    // wait for transmission complete(1)
    while (SPSR & (1 << SPIF) == 0)
        ;
    x = SPDR; // flashing SPDR
}