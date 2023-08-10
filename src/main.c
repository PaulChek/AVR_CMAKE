#include <util/delay.h>
#include "ports.h"
#include "dancing_leds.h"
#include "../spiI2cuart/spi.h"
#include "../spiI2cuart/max7219dm.h"
#include "../spiI2cuart/ssd1306.h"

volatile void rotate_bits(byte);

int main()
{
    SPI_Master_Init();
    Init_SSD1306();

    while (1)
    {
         SSD1306_COMMAND(ENTIRE_DISPLAY_ON_CMND);
    }
}