#include <util/delay.h>
#include "ports.h"
#include "dancing_leds.h"
#include "../spiI2cuart/spi.h"
#include "../spiI2cuart/max7219dm.h"
#include "../spiI2cuart/ssd1306.h"
#include "timer0.h"
#include "adc.h"
#include "font_small.h"

volatile void rotate_bits(byte);


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
            SSD1306_DRAW(5, font[li % 18]);
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