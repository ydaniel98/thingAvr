#ifndef io_s_h
#define io_s_h

#define OUT(DDR, PIN) 		DDR |= 1 << PIN
#define IN(DDR, PIN)  		DDR &= ~(1 << PIN)
#define MODE(DDR, PIN, M)	M ? OUT(DDR, PIN) : IN(DDR, PIN)

#define TOGGLE(PORT, PIN)	PORT ^= 1 << PIN
#define HIGH(PORT, PIN) 	PORT |= 1 << PIN
#define LOW(PORT, PIN)  	PORT &= ~(1 << PIN)

#define SET(PORT, PIN, S) 	S ? HIGH(PORT, PIN) : LOW(PORT, PIN)

#define READ(READ_R, PIN)	(READ_R & (1 << PIN))

#ifdef BTN_READ_SAMPLES

unsigned int btnLowSamples  = 0;
unsigned int btnHighSamples = 0;

uint8_t btnRead(volatile uint8_t readR, uint8_t pin) {
	while (1) {
		
		if (READ(readR, pin)) 
			btnHighSamples++;
		else
			btnHighSamples = 0;
			
		if (!READ(readR, pin))
			btnLowSamples++;
		else
			btnLowSamples = 0;
		
		if (btnHighSamples == BTN_READ_SAMPLES) {
			btnHighSamples = 0;
			return 1;
		}
			
		if (btnLowSamples == BTN_READ_SAMPLES) {
			btnLowSamples = 0;
			return 0;
		}
	}
}

#endif


#endif