#include <util/delay.h>
#include "ports.h"
#include "dancing_leds.h"
#include "spi.h"
#include "../spiI2cuart/spi.h"

volatile void rotate_bits( byte );

int main()
{
    DDRC = 0xFF;
    byte direction = 0;
    uint8_t delay_time = 100;
    // button
    DDRD |= 0 << 6;
    byte scheme_state = 0;
    while (1)
    {      
            if(PIND<<6 == 0){ scheme_state^=1;_delay_ms(200);}
            if(scheme_state)
            dance_leds(delay_time);
            delay_time--;
    }

    return 0;
}
