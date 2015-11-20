#ifndef PinGroup_cpp
#define PinGroup_cpp

#include <avr/io.h>
#include "PinGroup.h"
#include "Pin.h"

PinGroup::PinGroup(Pin *_pins_, uint8_t _bits_): pins(_pins_), bits(_bits_) {}

void PinGroup::clear() {
	for (uint8_t i=0; i < bits; i++) {
		pins[i].low();
	}
}

void PinGroup::overflow() {
	for (uint8_t i=0; i < bits; i++) {
        pins[i].high();
	}
}

void PinGroup::set(unsigned int n) {
	clear();
	for (uint8_t i=0; i < bits; i++) {
		if (n & (1 << (bits - 1 - i))) {
			pins[i].high();
			n &= ~(1 << (bits - 1 - i));
		}
	}
}

void PinGroup::mode(bool m) {
	for (uint8_t i=0; i < bits; i++) {
		pins[i].mode(m);
	}
}

unsigned int PinGroup::read() {
	unsigned int result = 0;
	for (unsigned int i=0; i < bits; i++) {
		if (pins[i].read())
			result |= 1 << (bits - 1 - i);
	}
	return result;
}

#endif