#ifndef Port_cpp
#define Port_cpp

#include <avr/io.h>
#include "Pin.h"
#include "structs.h"
#include "Port.h"
#include "io_s.h"

#define DDR  *(ddr)
#define PORT *(dPort)
#define PIN  *(readR)

Port::Port(PortData data) {
	ddr 	= data.ddr;
	dPort	= data.dPort;
	readR 	= data.readR;
}
Port::Port(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR): ddr(ddr), dPort(dPort), readR(readR) {}

void Port::set(uint8_t s) {
	PORT = s;
}

void Port::mode(uint8_t pin, bool m) {
	MODE(DDR, pin, m);
}

void Port::mode(bool m) {
	m ? DDR = 0xFF : DDR = 0x00;
}			

uint8_t Port::read() {
	return PIN;
}

bool Port::read(uint8_t pin) {
	return READ(PIN, pin);
}	

void Port::clear() {
	set(0x00);
}		

Pin Port::operator[](uint8_t pin) {
	return Pin((PortData){ddr, dPort, readR}, pin);
}

#endif
