#ifndef io_s_c
#define io_s_c

#include <avr/io.h>
#include "io_s.h"

uint8_t btnRead(volatile uint8_t *readR, uint8_t pin) {
	uint16_t btnLowSamples  = 0;
	uint16_t btnHighSamples = 0;
	while (1) {
		
		if (READ(*readR, pin)) 
			btnHighSamples++;
		else
			btnHighSamples = 0;
			
		if (!READ(*readR, pin))
			btnLowSamples++;
		else
			btnLowSamples = 0;
		
		if (btnHighSamples >= BTN_READ_SAMPLES) {
			btnHighSamples = 0;
			return 1;
		}
			
		if (btnLowSamples >= BTN_READ_SAMPLES) {
			btnLowSamples = 0;
			return 0;
		}
	}
}

#endif