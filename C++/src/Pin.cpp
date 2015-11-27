#ifndef Pin_cpp
#define Pin_cpp

#include <avr/io.h>
#include <util/delay.h>
#include "Pin.h"
#include "io_s.h"

Pin::Pin(PortData data, uint8_t pinNum): pinNum(pinNum) {
	ddr 	= data.ddr;
	dPort	= data.dPort;
	readR	= data.readR;
}

Pin::Pin(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR, uint8_t pinNum): ddr(ddr), dPort(dPort), readR(readR), pinNum(pinNum) {}

void Pin::high() {
	HIGH(*dPort, pinNum);
}

void Pin::low() {
	LOW(*dPort, pinNum);
}

void Pin::toggle() {
	TOGGLE(*dPort, pinNum);
}

bool Pin::read() {
	return READ(*readR, pinNum);
}

void Pin::set(bool s) {
	SET(*ddr, pinNum, s);
}

void Pin::mode(bool m) {
	MODE(*ddr, pinNum, m);
}
#endif