#ifndef PortDirect_h
#define PortDirect_h

#include <avr/io.h>
#include "structs.h"

class PortDirect {
public:
	PortData data;

	uint8_t read();			// Reads the value on the port
	void set(uint8_t s);	// Sets a value on the port
	bool readAll();			// Returns true if all pins are high
	void mode(bool m);		// Sets all pins OUTPUT or INPUT
	void clear();			// Puts 0x00 on port
	void overflow();		// Puts 0xFF on port
	
	PortDirect(PortData data);
	PortDirect(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR);
	PortDirect() {}
};

#endif