#include <util/delay.h>
#include "ports.h"
#include "dancing_leds.h"
#include "../spiI2cuart/spi.h"
#include "../spiI2cuart/max7219dm.h"
#include "../spiI2cuart/ssd1306.h"

volatile void rotate_bits(byte);
static byte font[][5] = {
    {0x7f, 0x08, 0x7f, 0}, //h
    {0x7f, 0x49, 0x49,0}, //e
    {0x7f, 0x40, 0x40,0}, //l
    {0x7f, 0x41, 0x7f,0}, // o
    };
int main()
{
    SPI_Master_Init();
    Init_SSD1306();
int count =0;
    while (1)
    {
        _delay_ms(5000);
        SSD1306_DRAW(4, font[0]);
        SSD1306_DRAW(4, font[1]);
        SSD1306_DRAW(4, font[2]);
        SSD1306_DRAW(4, font[2]);
        SSD1306_DRAW(4, font[3]);
         SSD1306_DATA(0);
         SSD1306_DATA(0);
         SSD1306_DATA(0);
         count++;
         if(count==30){count =0; SSD1306_clearDisplay(); }
    }
}