#include <util/delay.h>
#include "ports.h"
#include "dancing_leds.h"
#include "spi.h"
#include "../spiI2cuart/spi.h"
#include "../spiI2cuart/max7219dm.h"

volatile void rotate_bits(byte);
byte  fig1[8] ={0b00111100,0b01000010,0b10010101,0b10100001,0b10100001,0b10010101,0b01000010,0b00111100};
int main()
{
    DDRD |= CS_PIN; // init out pin for slave
    PORTB = 0x00;
    CS_OFF;
    SPI_Master_Init();
    LedM8x8_Init();
    _delay_ms(10);
    LedM8x8_Set();
    _delay_ms(600);
    LedM8x8_Clear();

    while (1)
    {
        LedM8x8_Show(fig1);
    }

    return 0;
}
// cs PD4
//  int main()
//  {

//     DDRC = 0xFF;
//     byte direction = 0;
//     uint8_t delay_time = 100;
//     // button
//     DDRD |= 0 << 6;
//     byte scheme_state = 0;
//     while (1)
//     {
//             if(PIND<<6 == 0){ scheme_state^=1;_delay_ms(200);}
//             if(scheme_state)
//             dance_leds(delay_time);
//             delay_time--;
//     }

//     return 0;
// }
