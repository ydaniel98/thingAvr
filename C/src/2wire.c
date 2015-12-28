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
			break;
		case T_WIRE_ACK:
			T_WIRE_SEND_ACK();
			break;
	}
	
	T_WIRE_WAIT_TWINT();						// Wait until the TWINT bit is cleared
	return (TWSR & TW_STATUS_MASK);				// Return the masked status register
}

uint8_t tWireWrite8(uint8_t addr, uint8_t data) {
	
	tWireStart();
	
	uint8_t twStatus;
	uint16_t r = 0;
	
	retry:
		if (r++ >= MAX_TRIES)
			goto endS;
		T_WIRE_GET_SLAVE_WRITE(addr, twStatus);
		if (!twStatus)
			goto retry;
	endS:
		twStatus = tWirePutData8(data);
		tWireEnd();
		return twStatus;
}


uint8_t tWireWriteA(uint8_t addr, uint8_t * data, uint8_t s) {
	tWireStart();
	
	uint8_t twStatus;
	uint16_t r = 0;
	
	retry:
		if (r++ >= MAX_TRIES)
			goto endS;
		T_WIRE_GET_SLAVE_WRITE(addr, twStatus);
		if (!twStatus)
			goto retry;
	endS:
		twStatus = tWirePutDataA(data, s);
		tWireEnd();
		return twStatus;
}


uint8_t tWireRead(uint8_t addr, uint8_t * buffer, uint16_t s) {
	tWireStart();
	
	uint8_t twStatus;
	uint16_t r = 0;
	
	retry:
		if (r++ >= MAX_TRIES)
			goto endS;
		T_WIRE_GET_SLAVE_READ(addr, twStatus);
		if (!twStatus)
			goto retry;
			
	if (!tWireReadBusA(buffer, s))
		twStatus = 0;
	
	endS:
		tWireEnd();
		return twStatus;
}

uint8_t tWireStart() {
	uint8_t twStatus;
	uint16_t r = 0;
	retry:
		if (r++ >= MAX_TRIES) 
			goto endS;
		T_WIRE_START_C(twStatus);
		if (!twStatus)
			goto retry;
	endS:
		return twStatus;
}	
									
void tWireEnd() {
	tWireTransmittion(T_WIRE_STOP);
}

uint8_t tWireAck() {
	return tWireTransmittion(T_WIRE_ACK) != TW_MR_DATA_NACK;
}	

uint8_t tWireNack() {
	return tWireTransmittion(T_WIRE_DATA) != TW_MR_DATA_ACK;
}									

uint8_t tWirePutData8(uint8_t data) {
	uint8_t twStatus;
	T_WIRE_WRITE_DATA(data, twStatus);
	return twStatus;
}	
					
uint8_t tWirePutDataA(uint8_t * data, uint16_t s) {
	uint8_t twStatus;
	uint16_t r = 0;
	retry:
		if (r++ >= MAX_TRIES)
			goto endS;
		for (; s >= 1; s--) {
			T_WIRE_WRITE_DATA(*data++, twStatus);
			if (!twStatus)
				goto retry;
		}
	endS:
		return twStatus;
}				

uint8_t tWireRequest(uint8_t addr, uint8_t request) {
	uint8_t twStatus;
	uint16_t r = 0;
	retryS:
		if (r++ >= MAX_TRIES)
			goto endS;
		T_WIRE_GET_SLAVE_WRITE(addr, twStatus);
		tWirePutData8(request);
		if (!twStatus)
			goto retryS;
	r = 0;
	retryF:
		if (r++ >= MAX_TRIES)
			goto endS;
		tWireStart();
		T_WIRE_GET_SLAVE_READ(addr, twStatus);
		if (!twStatus)
			goto retryF;
	endS:
		return twStatus;
	
}	
			
uint8_t tWireReadBus(uint8_t * buffer) {
	uint16_t retry = 0;
	retry:
		if (retry++ >= MAX_TRIES)
			goto endS;
		if (tWireAck()) {
			*buffer = TWDR;
			return 1;
		} else {
			goto retry;
		}
	endS:
		return 0;
}	
									
uint8_t tWireReadBusA(uint8_t * buffer, uint16_t s) {
	for (; s >= 1; s--) {
		if (!tWireReadBus(buffer++)) {
			return 0;
		}
	}
	return tWireNack();
}

#endif
