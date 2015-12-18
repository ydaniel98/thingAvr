#ifndef SEVEN_SEGMENTS_DECODER_h
#define SEVEN_SEGMENTS_DECODER_h

#include "io_s.h"
#include <avr/io.h>

#define PORT PORTD

/* Struct to hold the info for the bit used for the displays (2) max */
typedef struct {
	uint8_t shift;
	uint8_t mask;
}bitGroup;
/*********************************************************************/

void writeNum(uint8_t num, uint8_t shift, uint8_t mask);
void writeNum2(uint8_t num, bitGroup g1, bitGroup g2);

#endif