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
			return 1;
		case T_WIRE_DATA:
			T_WIRE_SEND_DATA();					// Sends the data in the tw data register
	}
	
	T_WIRE_WAIT_TWINT();						// Wait until the TWINT bit is cleared
	return (TWSR & TW_STATUS_MASK);				// Return the masked status register
}

uint8_t tWireWrite8(uint8_t data, uint8_t addr) {
	
	uint8_t twStatus;
	
	T_WIRE_START_C(twStatus);
	T_WIRE_GET_SLAVE_WRITE(addr, twStatus);
	T_WIRE_WRITE_DATA(data, twStatus);

	endS:
		tWireTransmittion(T_WIRE_STOP);
		return twStatus;
}


uint8_t tWireWriteA(uint8_t * data, uint8_t addr, uint8_t s) {
	
	uint8_t twStatus;
	
	T_WIRE_START_C(twStatus);
	T_WIRE_GET_SLAVE_WRITE(addr, twStatus);
	
	for (; s >= 1; s--) {
		T_WIRE_WRITE_DATA(*data++, twStatus);
	}
	
	endS:
		tWireTransmittion(T_WIRE_STOP);
		return twStatus;
}

uint8_t tWireRead(uint8_t addr, uint8_t * buffer, uint16_t s) {
	
	uint8_t twStatus;
	
	T_WIRE_START_C(twStatus);
	T_WIRE_GET_SLAVE_READ(addr, twStatus);
	
	for (; s >= 1; s--) {
		
		T_WIRE_READ_S();
		T_WIRE_WAIT_TWINT();
		
		if (TWSR == TW_MR_DATA_NACK) {
			twStatus = 0;
			goto endS;
		}
			
		*buffer++ = TWDR;
	}
	
	TWCR = _BV(TWEN) | _BV(TWINT);
	T_WIRE_WAIT_TWINT();

	endS:
		tWireTransmittion(T_WIRE_STOP);
		return twStatus;
}
#endif
