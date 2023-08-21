#include <util/delay.h>
#include <stdio.h>
#include "ports.h"
#include "dancing_leds.h"
#include "../spiI2cuart/spi.h"
#include "../spiI2cuart/max7219dm.h"
#include "../spiI2cuart/ssd1306.h"
#include "timer0.h"
#include "adc.h"
#include "font_small.h"
#include "Iwire.h"

// volatile void rotate_bits(byte);
char *uint64_tostring(uint64_t n, char str[static 21])
{
    if (!n)
    {
        str[0] = '0';
        return str;
    }

    str += 19;
    while (n)
    {
        *str-- = (n % 10) + '0';
        n /= 10;
    }
    return str + 1;
}
int main()
{
    SPI_Master_Init();
    Init_SSD1306();

    _delay_ms(2);
    setupTimer0(1000); //*10
    int16_t prev = timer0();
    // setupADC();
    cli();
    uint8_t serial_ds1820[8] ={0};
     IwireReadAddress(serial_ds1820);
    char serial_num[4] = {'\0'};
    sei();

    int i = 0;
    while (1)
    {
        if (prev - timer0() >= 30)
        {
            snprintf(serial_num, 4, "%u", serial_ds1820[i%8]);
            SSD1306_PRINT(serial_num);
            SSD1306_DATA(0);
            SSD1306_DATA(0);
            SSD1306_DATA(0);
            SSD1306_DATA(0);
            SSD1306_DATA(0);
            prev = timer0();
            i++;
            // ADCSRA |= (1 << 6);
        }

        if (timer0() <= 0)
        {
            SSD1306_clearDisplay();
            setupTimer0(1000);
            prev = timer0();
            PORTC ^= (1 << 3);
        }
    }
}