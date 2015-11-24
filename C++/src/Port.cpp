#ifndef Port_cpp
#define Port_cpp

#include <avr/io.h>
#include "Pin.h"
#include "structs.h"
#include "Port.h"

#define DDR  *(data.ddr)
#define PORT *(data.dPort)
#define PIN  *(data.readR)

Port::Port(PortData data): data(data) {}
Port::Port(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR) {
	data = PortData(ddr, dPort, readR);
}

void Port::set(uint8_t s) {
	PORT = s;
}

void Port::mode(uint8_t pin, bool m) {
	m ? DDR |= (1 << pin) : DDR &= ~(1 << pin);
}

void Port::mode(bool m) {
	m ? DDR = 0xFF : DDR = 0x00;
}			

uint8_t Port::read() {
	return PIN;
}

bool Port::read(uint8_t pin) {
	return PIN & (1 << pin);
}	

void Port::clear() {
	set(0x00);
}		

Pin Port::operator[](uint8_t pin) {
	return Pin(data, pin);
}

#endif
