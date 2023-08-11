#include <util/delay.h>
#include "ports.h"
#include "dancing_leds.h"
#include "../spiI2cuart/spi.h"
#include "../spiI2cuart/max7219dm.h"
#include "../spiI2cuart/ssd1306.h"
#include "timer0.h"
volatile void rotate_bits(byte);
static byte font[][5] = {
    {0x7f, 0x08, 0x08, 0x7f, 0}, // H
    {0x0, 0x0, 0x0, 0x0, 0},     // space
};

int main()
{
    SPI_Master_Init();
    Init_SSD1306();
    setupTimer0(500);
     int16_t prev = timer0();
    while (1)
    {
        if (prev - timer0() >= 15)
        {
            SSD1306_DRAW(5, font[0]);
            SSD1306_DRAW(5, font[1]);
                    prev = timer0();
        }
        
        if (timer0() <= 0)
        {
            SSD1306_clearDisplay();
            setupTimer0(500);
             prev = timer0();
        }

    }
}