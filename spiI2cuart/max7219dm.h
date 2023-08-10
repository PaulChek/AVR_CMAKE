/**
 * MAX7219 Datasheet
 * page 7
 *
 */
#ifndef MAX7219_H
#define MAX7219_H
#include "spi.h"
#include "../src/ports.h"
// digit registers represent row and bits int them colum
#define NO_OP_REG 0x00
#define DIGIT0_REG 0x01 // dig7 0x9
#define INTENSITY_REG 0x0A
#define SCAN_LIMIT_REG 0x0B // x7 for all lines
#define SHUTDOWN_REG 0x0C   // 0 or 1
#define DIPLAY_TEST_REG 0x0F
// slave
#define CS_PIN (1 << 4)
#define CS_ON PORTD &= ~CS_PIN
#define CS_OFF PORTD |= CS_PIN // always high for off
// Funs
void MasterTransmittToRegisterMAX7219(byte reg_address, byte data);
void LedM8x8_Init();
void LedM8x8_Clear();
void LedM8x8_Set();
void LedM8x8_Show(byte *bit_map);

#endif