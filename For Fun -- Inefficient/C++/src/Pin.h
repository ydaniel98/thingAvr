#ifndef Pin_h
#define Pin_h

#include "structs.h"
#include "io_s.h"

class Pin {
public:

	void high();			// Set pin high
	void low();				// Set pin low
	void toggle();			// Toogle pin
	bool read();			// Read pin

	void set(bool s);		// Set pin to s
	void mode(bool m);		// Sets pin's mode

	Pin(PortData data, uint8_t pinNum);
	Pin(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR, uint8_t pinNum);
	Pin() {};

private:
	volatile uint8_t *ddr;
	volatile uint8_t *dPort;
	volatile uint8_t *readR;

	uint8_t pinNum;
};

#endif