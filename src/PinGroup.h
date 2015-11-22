#ifndef PinGroup_h
#define PinGroup_h

#include <avr/io.h>

#include "Pin.h"

class PinGroup {
public:

	Pin *pins;
	uint8_t bits;

	void clear();				// Puts 0x00 on port
	void overflow();			// Sets the maximun value on port
	unsigned int read();		// Returns the value on the virtual port

	void mode(bool m);			// Sets the mode on the virtual port
	void set(unsigned int n);	// Puts the given value on the virtual port

	Pin operator[](uint8_t pin);
	
	PinGroup() {};
	PinGroup(Pin * _pins_, uint8_t _bits_);
};

#endif