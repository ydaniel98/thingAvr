#ifndef Port_h
#define Port_h

#include <avr/io.h>
#include "Pin.h"
#include "structs.h"

class Port: Pin {
public:
	void set(uint8_t s);					// Sets the number s on the port
	void clear();

	void mode(uint8_t pin, bool m);			// Sets the mode for an specific pin
	void mode(bool m);						// Sets mode for for all pins on port

	uint8_t read(); 						// Reads the value on the port
	bool read(uint8_t pin); 				// Reads an specific pin

	Pin operator[](uint8_t pin);

	Port(PortData data);
	Port(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR);
	Port() {}

private:
	volatile uint8_t *ddr;
	volatile uint8_t *dPort;
	volatile uint8_t *readR;
};

#endif