#ifndef SSD_1306_
#define SSD_1306_

#include "../src/ports.h"
#include <util/delay.h>
#include "spi.h"

/**
 * https://pdf1.alldatasheet.com/datasheet-pdf/view/1179026/ETC2/SSD1306.html
 * 1. Fundamental Command Table*/
#define SET_CONTRAST_CMND 0x81          // two byte 1: cmnd ,2: 1-> 256
#define ENTIRE_DISPLAY_ON_CMND 0xA5     // Entire Display On Output ignores RAM content
#define RESUME_TO_RAM_CONTENT_CMND 0xA4 // Back show img from RAM
#define NORMAL_CMND 0xA6                // INVERSE TO NORMAL MODE
#define INVERSE_CMND 0xA7               // NORMAL TO  INVERSE  MODE
#define DISPLAY_ON_CMND 0xAF            // Display on
#define DISPLAY_OFF_CMND 0xAE           // Display off
/**
 * 2. Scrolling Command Table*/

/////////////////////

/**
 * 3. Addressing Setting Command Table */
#define SET_ADDRESSING_MODE_CMND 0x20 // 2byte command
#define SET_HORIZONTAL_MODE 0b00      // Horizontal addressing mode
#define SET_VERTICAL_MODE 0b01        // Vertical addressing mode
#define SET_PAGE_MODE 0b10            // PAGE addressing mode

// FOR H V mode only
#define SET_COL_ADDRESS_CMND 0x21  // 3 byte command [CMND], [CAS:0-127], [CAE:0-127]
#define SET_PAGE_ADDRESS_CMND 0x22 // 3 byte command [CMND], [PAS:0-7], [PAE:0-7]

/**
 * 4. Hardware Configuration (Panel resolution & layout related) Command Table
 */
#define CHARGE_PUMP_CMND 0x8d
#define CHARGE_PUMP_ENABLE 0x14
#define CHARGE_PUMP_DISABLE 0x10
// FUNCTIONS
// CS
#define PIN_CS_SSD1306 (1 << 7) // PORTD
#define CS_SSD1306_ON PORTD &= ~PIN_CS_SSD1306
#define CS_SSD1306_OFF PORTD |= PIN_CS_SSD1306

// DC
#define PIN_DC_SSD1306 (1 << 6)                  // PORTD Data or command pin
#define COMMAND_SSD1306 PORTD &= ~PIN_DC_SSD1306 // LOW for command
#define DATA_SSD1306 PORTD |= PIN_DC_SSD1306     // High for data

#define PIN_RESET_SSD1306 (1 << 5)
#define RESET_SSD1306_LOW PORTD &= ~PIN_RESET_SSD1306
#define RESET_SSD1306_HIGH PORTD |= PIN_RESET_SSD1306

// FUNs
void SSD1306_DATA(byte data)
{
    DATA_SSD1306;
    CS_SSD1306_ON;
    SPI_Master_Transmit(data);
    CS_SSD1306_OFF;
};

void SSD1306_COMMAND(byte command)
{
    COMMAND_SSD1306;
    CS_SSD1306_ON;
    SPI_Master_Transmit(command);
    CS_SSD1306_OFF;
}
void SSD1306_clearDisplay();
void Init_SSD1306()
{
    PORTD = 0;
    DDRD = 0;
    DDRD = PIN_CS_SSD1306 | PIN_DC_SSD1306 | PIN_RESET_SSD1306; // 7,6,5 output

    // pull-up
    RESET_SSD1306_HIGH;
    CS_SSD1306_OFF;
    DATA_SSD1306;
    _delay_ms(10);

    // Power on chip
    RESET_SSD1306_LOW;
    _delay_us(3);
    RESET_SSD1306_HIGH;
    // charge pump
    _delay_ms(150);
    SSD1306_COMMAND(CHARGE_PUMP_CMND);
    SSD1306_COMMAND(CHARGE_PUMP_ENABLE);
    _delay_ms(10);

    // memory map
    SSD1306_COMMAND(SET_ADDRESSING_MODE_CMND);
    SSD1306_COMMAND(SET_HORIZONTAL_MODE);

    // REMAP
    SSD1306_COMMAND(0xc8);
    SSD1306_COMMAND(0xDA);
    SSD1306_COMMAND(0x12);
    SSD1306_COMMAND(0xA1); // col 127 to 0;

    // turn on display
    _delay_ms(150);
    SSD1306_COMMAND(DISPLAY_ON_CMND);

    // clear display
    SSD1306_clearDisplay();
}
void SSD1306_clearDisplay()
{
    SSD1306_COMMAND(SET_PAGE_ADDRESS_CMND);
    SSD1306_COMMAND(0);
    SSD1306_COMMAND(7);
    SSD1306_COMMAND(SET_COL_ADDRESS_CMND);
    SSD1306_COMMAND(0);
    SSD1306_COMMAND(127);
    for (int i = 0; i <= 128 * 64 / 8; i++)
        SSD1306_DATA(0);
}
// write banch
void SSD1306_DRAW(uint32_t size, byte *array)
{
    do
    {
        SSD1306_DATA(*(array++));
    } while (--size);
}
#endif