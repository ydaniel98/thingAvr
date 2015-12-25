#ifndef two_wire_h
#define two_wire_h

#include <avr/io.h>
#include <util/twi.h>

#define T_WIRE_START	0x00
#define T_WIRE_DATA		0x01
#define T_WIRE_STOP		0x02

#define T_WIRE_WRITE	0x00
#define T_WIRE_READ		0x01

#define T_WIRE_WAIT_TWINT() while (!(TWCR & _BV(TWINT)))
#define T_WIRE_SETUP()		TWCR |= _BV(TWEN)
#define T_WIRE_READ_S()		TWCR = _BV(TWEA) |_BV(TWEN) | _BV(TWINT);

#define T_WIRE_SEND_START() TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTA)
#define T_WIRE_SEND_STOP()	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTO)
#define T_WIRE_SEND_DATA()	TWCR = _BV(TWEN) | _BV(TWINT)

#define T_WIRE_GET_ID(ADDR, RW) ((ADDR << 1) | RW)

uint8_t tWireTransmittion(uint8_t a);
uint8_t tWireWrite8(uint8_t data, uint8_t addr);

uint8_t tWireGetSlaveWrite(uint8_t addr);
uint8_t tWireGetSlaveRead(uint8_t addr);

uint8_t tWireWriteNS(uint8_t data);									// Sends byte with not stop condition and no address
uint8_t tWireWriteA(uint8_t * data, uint8_t addr, uint8_t s);		// Sends all the bytes in the pointer

uint8_t tWireRead(uint8_t addr, uint8_t * buffer, uint16_t s);		// Gets data and sets it on the buffer

#endif