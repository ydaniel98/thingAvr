#ifndef analog_c
#define analog_c

#include <avr/io.h>
#include "analog.h"

void analogSetup() {
	
	#ifdef AREF
	ADMUX = 0x0;	// Aref as voltage reference
	#endif
	
	#ifdef AVCC
	ADMUX = 0x40;	// Voltage reference as vcc
	#endif
	
	#ifdef INTERN_AVCC
	ADMUX = 0xC0;	// Voltage reference as internal 2.56 V
	#endif
	
	/* Analog frequency */
	#if ADC_DIV_FACTOR == 2
	ADCSRA = 0x80;
	#endif
	
	#if ADC_DIV_FACTOR == 4
	ADCSRA = 0x82;
	#endif
	
	#if ADC_DIV_FACTOR == 8
	ADCSRA = 0x83;
	#endif
	
	#if ADC_DIV_FACTOR == 16
	ADCSRA = 0x84;
	#endif
	
	#if ADC_DIV_FACTOR == 32
	ADCSRA = 0x85;
	#endif
	
	#if ADC_DIV_FACTOR == 64
	ADCSRA = 0x86;
	#endif
	
	#if ADC_DIV_FACTOR == 128
	ADCSRA = 0x87;
	#endif
	/********************/
	
	
}

uint16_t analogRead(uint8_t channel) {
	
	channel &= 0x07;
	ADMUX = (ADMUX & 0xF8) | channel;
	
	ADCSRA |= (1 << ADSC);				// Start Conversion
	
	while(ADCSRA & (1 << ADSC));
	
	return ADC;
	
}

#endif















