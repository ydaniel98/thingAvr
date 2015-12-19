#ifndef io_s_h
#define io_s_h

#include <avr/io.h>

#define OUT(DDR, PIN) 		DDR |= 1 << PIN
#define IN(DDR, PIN)  		DDR &= ~(1 << PIN)
#define MODE(DDR, PIN, M)	M ? OUT(DDR, PIN) : IN(DDR, PIN)

#define TOGGLE(PORT, PIN)	PORT ^= 1 << PIN
#define HIGH(PORT, PIN) 	PORT |= 1 << PIN
#define LOW(PORT, PIN)  	PORT &= ~(1 << PIN)

#define SET(PORT, PIN, S) 	S ? HIGH(PORT, PIN) : LOW(PORT, PIN)

#define READ(READ_R, PIN)	(READ_R & (1 << PIN))

#define WRITE_BITS(NUM, PORT, SHIFT, MASK)	PORT = (PORT & ~MASK) | ((NUM << SHIFT) & MASK)
#define READ_BITS(READ_R, SHIFT, MASK)		((READ_R & MASK) >> SHIFT)

#define BTN_READ_SAMPLES 6000
#ifdef BTN_READ_SAMPLES

uint8_t btnRead(volatile uint8_t readR, uint8_t pin);

#endif

#endif