#ifndef analog_h
#define analog_h

#include <avr/io.h>

#define AVCC
#define ADC_DIV_FACTOR 128

void analogSetup();							// Sets up the analog registers
uint16_t analogRead(uint8_t channel);		// Reads the value in the given analog channel

#endif









