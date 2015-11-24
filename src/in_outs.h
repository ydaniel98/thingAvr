#ifndef in_outs_h
#define in_outs_h

#define OUT(DDR, PIN) 		DDR |= 1 << PIN
#define IN(DDR, PIN)  		DDR &= ~(1 << PIN)
#define MODE(DDR, PIN, M)	M ? OUT(DDR, PIN) : IN(DDR, PIN)

#define TOGGLE(PORT, PIN)	PORT ^= 1 << PIN
#define HIGH(PORT, PIN) 	PORT |= 1 << PIN
#define LOW(PORT, PIN)  	PORT &= ~(1 << PIN)

#define SET(PORT, PIN, S) 	S ? HIGH(PORT, PIN) : LOW(PORT, PIN)

#define READ(READ_R, PIN)	READ_R & (1 << PIN)


#endif