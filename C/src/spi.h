#ifndef spi_h
#define spi_h

#include <avr/io.h>

#define SPI_4_DIV_FACTOR				0x00
#define SPI_16_DIV_FACTOR				(1 << SPR0)
#define SPI_64_DIV_FACTOR				(1 << SPR1)
#define SPI_128_DIV_FACTOR				(1 << SPR1) | (1 << SPR0)

#define SPI_DATA_MSB_FIRST				0x00
#define SPI_DATA_LSB_FIRST				(1 << DORD)

#define SPI_CLOCK_IDLE_HIGH				(1 << CPOL)
#define SPI_CLOCK_IDLE_LOW				0x00

#define SPI_CLOCK_PHASE_SAMPLE_LEADING	0x00
#define SPI_CLOCK_PHASE_SETUP_LEADING	(1 << CPHA)

#define SPI_SETUP_MASTER(DIV_FACTOR, DATA_ORDER, CLOCK_POL, CLOCK_PHASE)	SPCR = (1 << SPE) | (1 << MSTR) | DIV_FACTOR | DATA_ORDER | CLOCK_POL | CLOCK_PHASE
#define SPI_SETUP_SLAVE(DATA_ORDER, CLOCK_POL, CLOCK_PAHSE)					SPCR = (1 << SPE) | DATA_ORDER | CLOCK_POL | CLOCK_PHASE

uint8_t spiTranceiver(uint8_t data);


#endif