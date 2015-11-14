#ifndef Display_cpp
#define Display_cpp

#include <avr/io.h>
#include "PortVirtual.h"
#include "Pin.h"
#include "Display.h"
#include "parse.h"
#include "convenience.h"

/* TODO: use atoi to parse int */


Display::Display(decoder4bitMap *_decodMap_, uint8_t _digits_): PortVirtual(portBuffer, 4), decodMap(_decodMap_), digits(_digits_) {
	for (uint8_t i=0; i < digits; i++) {
		setBuffer(decodMap[i]);
		mode(OUTPUT);				// Make Sure all pins are set to ouput
	}
}

void Display::write(uint32_t w) {

	if (lastWrite == w)
		return;
	
	lastWrite = w;

	uint8_t pos = parseInt(w, parse);				// Parsed number

	if (pos >= digits)								// Check if digit was not overflow
		return overflowDisp();

	update(pos);									// Update display

	for (; pos >=0; pos--) {
		setBuffer(decodMap[digits - pos - 1]);		// Set buffer for display
		set(parse[pos]);							// Set the number
		if (pos == 0)
			return;
	}

}				

void Display::clearDisp() {
	update(0x00); // Clear display using update
}

void Display::test() {
	for (uint8_t i=0; i < digits; i++) {
		setBuffer(decodMap[i]);
		set(0x08);
	}
}		

void Display::overflowDisp() {
	for (uint8_t i=0; i < digits; i++) {
		setBuffer(decodMap[i]);
		set(0x09);
	}
}			

void Display::setBuffer(decoder4bitMap dc4M) {
	portBuffer[3] = dc4M.a;
	portBuffer[2] = dc4M.b;
	portBuffer[1] = dc4M.c;
	portBuffer[0] = dc4M.d;
}

void Display::update(uint8_t digitUpdatePoint) {
	for (; digitUpdatePoint < digits; digitUpdatePoint++) {
		setBuffer(decodMap[digitUpdatePoint]);
		set(0x00);
	}
}


#endif