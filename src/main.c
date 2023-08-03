#include "ports.h"
#include <util/delay.h>

volatile void rotate_bits(volatile byte *);
void my_delay(uint8_t t){
    while(t--)
    __builtin_avr_delay_cycles(F_CPU/1000);//1ms
}
int main()
{
    DDRC = 0xFF;
    PORTC = 1;
    byte direction = 0;
    byte i = 7;
    uint8_t delay_time = 200;
    while (1)
    {
          
        while (my_delay(delay_time),PORTC <<= 1,--i);
      
        delay_time--;

        while (my_delay(delay_time),PORTC >>= 1,++i<7);
    }

    return 0;
}
