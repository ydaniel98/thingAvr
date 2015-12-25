#ifndef two_wire_c
#define two_wire_c

#include <avr/io.h>
#include <util/twi.h>
#include "2wire.h"

uint8_t tWireTransmittion(uint8_t a) {
	switch (a) {
		case T_WIRE_START:
			T_WIRE_SEND_START();				// Sends the start condition
			break;
		case T_WIRE_STOP:
			T_WIRE_SEND_STOP();					// Sends the stop condition
			break;
		case T_WIRE_DATA:
			T_WIRE_SEND_DATA();					// Sends the data in the tw data register
	}
	
	T_WIRE_WAIT_TWINT();						// Wait until the TWINT bit is cleared
	return (TWSR & TW_STATUS_MASK);				// Return the masked status register
}

uint8_t tWireWrite8(uint8_t data, uint8_t addr) {
	if (!tWireGetSlaveWrite(addr))
		return 0;
	data = tWireWriteNS(data);
	tWireTransmittion(T_WIRE_STOP);
	return (data);
}

uint8_t tWireWriteNS(uint8_t data) {
	TWDR = data;
	return (tWireTransmittion(T_WIRE_DATA) == TW_MT_DATA_ACK);
}

uint8_t tWireWriteA(uint8_t * data, uint8_t addr, uint8_t s) {
	if (!tWireGetSlaveWrite(addr))
		return 0;
	addr = 1;
	for (; s >= 1; s--) {
		if (!tWireWriteNS(*data++)) {
			addr = 0;
			break;
		}
	}
	tWireTransmittion(T_WIRE_STOP);
	return addr;
}

uint8_t tWireGetSlaveWrite(uint8_t addr) {
	uint8_t twStatus;

	twStatus = tWireTransmittion(T_WIRE_START);

	if ((twStatus == TW_MT_ARB_LOST) || ((twStatus == TW_MT_SLA_NACK) && (twStatus != TW_REP_START))) 
		return 0;

	TWDR = addr << 1;
	twStatus = tWireTransmittion(T_WIRE_DATA);

	return ((twStatus != TW_MT_SLA_NACK) || (twStatus != TW_MT_ARB_LOST) || (twStatus == TW_MT_SLA_ACK));
}

uint8_t tWireGetSlaveRead(uint8_t addr) {
	uint8_t twStatus;

	twStatus = tWireTransmittion(T_WIRE_START);

	if ((twStatus == TW_MR_ARB_LOST) || ((twStatus == TW_MR_SLA_NACK) && (twStatus != TW_REP_START)))
	return 0;

	TWDR = addr << 1 | 1;
	twStatus = tWireTransmittion(T_WIRE_DATA);

	return ((twStatus != TW_MR_SLA_NACK) || (twStatus != TW_MR_ARB_LOST) || (twStatus == TW_MR_SLA_ACK));
}

uint8_t tWireRead(uint8_t addr, uint8_t * buffer, uint16_t s) {
	if (!tWireGetSlaveRead(addr))
		return 0;
	for (; s >= 1; s--) {
		T_WIRE_READ_S();
		T_WIRE_WAIT_TWINT();
		*buffer++ = TWDR;
	}
	TWCR = _BV(TWEN) | _BV(TWINT);
	T_WIRE_WAIT_TWINT();
	tWireTransmittion(T_WIRE_STOP);
	return 1;
}
#endif
