/** SPI – Serial Peripheral Interface
 *Page 136 datasheet mt32a
 *
 */
#ifndef _SPI
#define _SPI

typedef unsigned char byte;
// defining spi registrers
#define SPDR *((volatile byte *)0x2F) // Data Register or Shift Register

#define SPSR *((volatile byte *)0x2E) //  Status Register [SPIF WCOL x x x x x SPI2X]
#define SPIF 7                        // SPI Interrupt Flag When a serial transfer is complete, the SPIF Flag is set

#define SPCR *((volatile byte *)0x2D) // Control Register [SPIE SPE DORD MSTR CPOL CPHA SPR1 SPR0]
#define MSTR 4                        // Master/Slave Select
#define SPE 6                         // When the SPE bit is written to one, the SPI is enabled.
#define SPR0 0                        // Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0

// DDRB actually in atmega32
#define DDR_SPI *((volatile byte *)0x37) // data direction for spi DDRB
#define MOSI 5                           // PB5
#define SCK 7                            // PB7

// Functions prototype
void SPI_Master_Init(void);
void SPI_Master_Transmit(unsigned char data);

#endif