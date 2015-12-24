#ifndef uart_c
#define uart_c

#include <avr/io.h>
#include <stdlib.h>

void uartWrite(uint8_t data) {
	UCSR0A &= ~((1 << UPE0) | (1 << DOR0));
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void uartWriteS(const char *s) {
	while (*s)
		uartWrite(*s++);
	uartWrite('\0');
}

void uartWriteCN(int n, uint8_t radix) {
	char buffer[11];
	itoa(n, buffer, radix);
	uartWriteS(buffer);
}

void uartWriteln(const char *s) {
	uartWriteS(s);
	uartWrite(13);
}

uint8_t uartRead() {
	while(!((UCSR0A) & (1 << RXC0)));
	return UDR0;
}

void uartReadS(uint8_t * buffer, uint16_t s) {
	
	if (s == 0)
		return;
		
	do {
		
		if (s == 1) {
			*buffer = '\0';
			return;
		}
		
		*buffer = uartRead();
		s--;
		
	} while (*buffer++);
}
#endif
