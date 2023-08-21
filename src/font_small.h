#ifndef FONT_SMALL_H
#define FONT_SMALL_H
const static unsigned char font[][5] = {
    {0b01000000, 0, 0, 0, 0},                            // .
    {0b01100000, 0b00010000, 0b00001100, 0b00000011, 0}, // /
    {0b00111110, 0b01010001, 0b01000101, 0b00111110, 0}, // 0
    {0b01000100, 0b01000010, 0b01111111, 0b01000000, 0}, // 1
    {0b01100110, 0b01010001, 0b01001001, 0b01000110, 0}, // 2
    {0b00100010, 0b01000001, 0b01001001, 0b00110110, 0}, // 3
    {0b00011111, 0b00010000, 0b00010000, 0b01111111, 0}, // 4
    {0b01001111, 0b01001001, 0b01001001, 0b00110001, 0}, // 5
    {0b00111110, 0b01001001, 0b01001001, 0b00110010, 0}, // 6
    {0b01100001, 0b00010001, 0b00001001, 0b00000111, 0}, // 7
    {0b00110110, 0b01001001, 0b01001001, 0b00110110, 0}, // 8
    {0b00100110, 0b01001001, 0b01001001, 0b00110110, 0}, // 9

    {0b00111110, 0b01000001, 0b01000001, 0b00111110, 0}, // o
    {0b01111110, 0b00010001, 0b00010001, 0b01111110, 0}, // A
    {0b00111111, 0b01000000, 0b01000000, 0b00111111, 0}, // U
    {0x7f, 0x08, 0x08, 0x7f, 0},                         // H
    {0b00011111, 0b01100000, 0b01100000, 0b00011111, 0}, // V
    {0, 0x10, 0x10, 0x10, 0},                            // -
    {0x0, 0x0, 0x0, 0x0, 0},                             // space
};

#endif