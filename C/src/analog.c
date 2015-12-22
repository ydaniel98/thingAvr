#ifndef analog_c
#define analog_c

#include <avr/io.h>
#include "analog.h"

uint16_t analogRead(uint8_t channel) {
	
	channel &= 0x07;
	ADMUX = (ADMUX & 0xF8) | channel;
	
	ADCSRA |= (1 << ADSC);				// Start Conversion
	
	while(ADCSRA & (1 << ADSC));
	
	return ADC;
	
}

#endif















