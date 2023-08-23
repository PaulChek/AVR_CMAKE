#include <util/delay.h>
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

int main()
{
    SPI_Master_Init();
    Init_SSD1306();

    _delay_ms(2);
    setupTimer0(1000); //*10
    int16_t prev = timer0();
    // setupADC();
    cli();
    uint8_t serial_ds1820[8] = {0};
    IwireReadAddress(serial_ds1820);
    uint8_t reg[] = {0x48, 0x46, 0b00011111};
    SetDS18B20Resolution(serial_ds1820, reg);
    sei();

    int i = 0;
    while (1)
    {
        if (prev - timer0() >= 30)
        {
            cli();
            char *temp = DS18B20GetTemperature(serial_ds1820);
            sei();
            SSD1306_PRINT(temp);
            SSD1306_DATA(0);
            SSD1306_DATA(0);
            SSD1306_DATA(0);
            SSD1306_DATA(0);
            SSD1306_DATA(0);
            prev = timer0();
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