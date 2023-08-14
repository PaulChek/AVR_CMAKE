#ifndef ADC_H_
#define ADC_H_
#include <avr/interrupt.h>
#include "../spiI2cuart/ssd1306.h"
#include "ports.h"
// Regs
#define ACSR *((volatile unsigned char *)0x28)   // Analog Comparator Control and Status Register [ACD ACBG ACO ACI ACIE ACIC ACIS1 ACIS0]
#define ADMUX *((volatile unsigned char *)0x27)  // Multiplexer [REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0]
#define ADCSRA *((volatile unsigned char *)0x26) // Control and Status [ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0]
#define ADCH *((volatile unsigned char *)0x25)   // Data reg ho
#define ADCL *((volatile unsigned char *)0x24)   // Data reg lo
#define SFIOR *((volatile unsigned char *)0x50)  //  Special Function I/O Register
#define SREG *((volatile unsigned char *)0x5f)   //

void setupADC()
{
    DDRA &= ~(1 << 0);            // port a as input
                                  //   ACSR |= (1 << 3);  // interrupt flag
    ADMUX = 0b0000;               // ADC0
    ADMUX |= (1 << 6) | (0 << 5); // Ref 01 ot AVCC voltage ref LDRA
    ADCSRA = 0b111;               // 128 prescaler
    ADCSRA |= (1 << 7) | (0 << 5) | (1 << 3);
    // SFIOR |= (1 << 5); // free running mode
    SREG |= (1 << 7);
}
ISR(ADC_vect,ISR_NOBLOCK)
{
    int tmp = ADCL | (ADCH << 8);

    contrast = tmp >> 2;
    SSD1306_COMMAND(SET_CONTRAST_CMND);
    SSD1306_COMMAND(contrast);
    ADCSRA &= ~(0 << 4); // clear adcif flag
}

#endif