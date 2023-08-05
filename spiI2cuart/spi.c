#include "spi.h"

void SPI_Master_Init()
{
    /* Set MOSI and SCK output*/
    DDR_SPI = (1 << MOSI) | (1 << SCK);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}