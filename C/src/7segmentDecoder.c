#ifndef SEVEN_SEGMENTS_DECODER_c
#define SEVEN_SEGMENTS_DECODER_c

#include "7segmentDecoder.h"
#include "avr/io.h"
#include "io_s.h"

void writeNum(uint8_t num, uint8_t shift, uint8_t mask) {
	WRITE_BITS(num, PORT, shift, mask);
}

void writeNum2(uint8_t num, bitGroup g1, bitGroup g2) {
	WRITE_BITS(((num - (num % 10)) / 10), PORT, g1.shift, g1.mask);
	WRITE_BITS((num % 10), PORT, g2.shift, g2.mask);
}

#endif