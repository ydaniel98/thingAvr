#ifndef io_s_c
#define io_s_c

#include <avr/io.h>
#include "io_s.h"

unsigned int btnLowSamples  = 0;
unsigned int btnHighSamples = 0;

uint8_t btnRead(volatile uint8_t readR, uint8_t pin) {
	while (1) {
		
		if (READ(readR, pin)) 
			btnHighSamples++;
		else
			btnHighSamples = 0;
			
		if (!READ(readR, pin))
			btnLowSamples++;
		else
			btnLowSamples = 0;
		
		if (btnHighSamples == BTN_READ_SAMPLES) {
			btnHighSamples = 0;
			return 1;
		}
			
		if (btnLowSamples == BTN_READ_SAMPLES) {
			btnLowSamples = 0;
			return 0;
		}
	}
}

#endif