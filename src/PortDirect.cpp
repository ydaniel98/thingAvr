#ifndef PortDirect_cpp
#define PortDirect_cpp

#include <avr/io.h>
#include <util/delay.h>
#include "PortDirect.h"

PortDirect::PortDirect(PortData data): data(data) {}
PortDirect::PortDirect(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR) {
	data = PortData(ddr, dPort, readR);
}

void PortDirect::mode(bool m) {
	m ? *(data.ddr) = 0xFF : *(data.ddr) = 0x00;	// All output or all input
}

void PortDirect::set(uint8_t s) {
	*(data.dPort) = s;
}

uint8_t PortDirect::read() {
	return *(data.readR);
}

void PortDirect::clear() {
	set(0x00);
}

void PortDirect::overflow() {
	set(0xFF);
}

#endif