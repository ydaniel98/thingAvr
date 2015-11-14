#ifndef PortVirtual_cpp
#define PortVirtual_cpp

#include <avr/io.h>
#include "PortVirtual.h"
#include "Pin.h"

PortVirtual::PortVirtual(Pin *_pins_, uint8_t _bits_): pins(_pins_), bits(_bits_) {}

void PortVirtual::clear() {
	for (uint8_t i=0; i < bits; i++) {
		pins[i].low();
	}
}

void PortVirtual::overflow() {
	for (uint8_t i=0; i < bits; i++) {
        pins[i].high();
	}
}

void PortVirtual::set(unsigned int n) {
	clear();
	for (uint8_t i=0; i < bits; i++) {
		if (n & (1 << (bits - 1 - i))) {
			pins[i].high();
			n &= ~(1 << (bits - 1 - i));
		}
	}
}

void PortVirtual::mode(bool m) {
	for (uint8_t i=0; i < bits; i++) {
		pins[i].mode(m);
	}
}

bool PortVirtual::readAll() {
	bool r = 1;
	for (uint8_t i=0; i < bits; i++) {
		r = r && pins[i].read();
	}
	return r;
}

unsigned int PortVirtual::read() {
	unsigned int result = 0;
	for (unsigned int i=0; i < bits; i++) {
		if (pins[i].read())
			result |= 1 << (bits - 1 - i);
	}
	return result;
}

#endif