#ifndef spi_c
#define spi_c

#include "spi.h"

uint8_t spiTranceiver(uint8_t data) {
	SPDR= data;
	while(!(SPSR & (1 << SPIF)));
	return data;
}


#endif