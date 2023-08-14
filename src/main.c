#include <util/delay.h>
#include "ports.h"
#include "dancing_leds.h"
#include "../spiI2cuart/spi.h"
#include "../spiI2cuart/max7219dm.h"
#include "../spiI2cuart/ssd1306.h"
#include "timer0.h"
#include "adc.h"

volatile void rotate_bits(byte);
static byte font[][5] = {
    {0b01111110, 0b00010001, 0b00010001, 0b01111110, 0}, // A 4
    {0b00111111, 0b01000000, 0b01000000, 0b00111111, 0}, // U 5
    {0x7f, 0x08, 0x08, 0x7f, 0},                         // H 0
    {0b00011111, 0b01100000, 0b01100000, 0b00011111, 0}, // V 6
    {0b01000000, 0, 0, 0, 0},                            // . 2
    {0, 0x10, 0x10, 0x10, 0},                            // - 3
    {0x0, 0x0, 0x0, 0x0, 0},                             // space 1
};

int main()
{
    SPI_Master_Init();
    Init_SSD1306();

    // set puttons
    DDRD &= ~(1 << 3);            // INT1 as input
    DDRD &= ~(1 << 2);            // INT0 as input
    PORTD |= (1 << 3) | (1 << 2); // pull up

    DDRC |= (1 << 3); // led tx
    PORTC |= (1 << 3);
    _delay_ms(2);
    setupTimer0(1000); //*10

    uint8_t li = 0;
    int16_t prev = timer0();
    setupADC();

    while (1)
    {
        if (prev - timer0() >=15)
        {
            SSD1306_DRAW(5, font[li % 7]);
            prev = timer0();
              ADCSRA|=(1<<6);
              li++;
        }

        if (timer0() <= 0)
        {
            SSD1306_clearDisplay();
            setupTimer0(1000);
            prev = timer0(); 
             PORTC ^= (1 << 3);
        }
       
    }
    
    return 0;
}