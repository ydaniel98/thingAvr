#ifndef Pin_cpp
#define Pin_cpp

#include <avr/io.h>
#include <util/delay.h>
#include "Pin.h"
#include "convenience.h"

Pin::Pin(PortData data, uint8_t pinNum): data(data), pinNum(pinNum) {}
Pin::Pin(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR, uint8_t pinNum): pinNum(pinNum) {
	data = PortData(ddr, dPort, readR);
}

void Pin::high() {
	set(1);
}

void Pin::low() {
	set(0);
}

void Pin::toggle() {
	*(data.dPort) ^= 1 << pinNum;
}

bool Pin::read() {
	return *(data.readR) & (1 << pinNum);
}

void Pin::set(bool s) {
	s ? *(data.dPort) |= 1 << pinNum : *(data.dPort) &= ~(1 << pinNum);
}

void Pin::mode(bool m) {
	m ? *(data.ddr) |= 1 << pinNum : *(data.dPort) &= ~(1 << pinNum);
}
#endif