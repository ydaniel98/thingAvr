#ifndef uart_h
#define uart_h

#include <avr/io.h>

#define BAUDRATE_REGISTER ((F_CPU)/(BAUDRATE*16UL) - 1)

#define UART_RECEIVER			(1 << RXEN0)
#define UART_TRANSMITTER		(1 << TXEN0)
#define UART_EVEN_PARTY_BITS	(1 << UPM01)
#define UART_ODD_PARTY_BITS		(1 << UPM01) | (1 << UPM00)
#define UART_NO_PARTY_BITS		0x00

#define UART_SETUP(RECEIVER, TRANSMITTER, STOP, PARTY) UBRR0H = (BAUDRATE_REGISTER >> 8); UBRR0L = BAUDRATE_REGISTER; UCSR0B |= RECEIVER | TRANSMITTER; UCSR0C |= PARTY | STOP

#define UART_DATA_READY			(UCSR0A & (1 << RXC0))
#define UART_DATA_OVER_RUN		(UCSR0A & (1 << DOR0))
#define UART_PARTY_BITS_ERROR	(UCSR0A & (1 << UPE0))

#define UART_1_STOP_BIT			0x00
#define UART_2_STOP_BITS		(1 << USBS0)

void uartWrite(uint8_t t);
void uartWriteS(const char *s);
void uartWriteCN(int n, uint8_t radix);
void uartWriteln(const char *s);

uint8_t uartRead();
void uartReadS(uint8_t * buffer, uint16_t s);

#endif 