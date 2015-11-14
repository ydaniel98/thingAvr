#ifndef structs_h
#define structs_h

/* This file contains all the structs (support structs) for other structs or classes, the ones that are used globaly */
/* Holds the data necesary for the creation of a pin */

typedef struct PortData {
	volatile uint8_t *ddr; 		// Data Direction register
	volatile uint8_t *dPort;		// Output port
	volatile uint8_t *readR;		// Read port (PINB, PIND, etc)

	PortData(volatile uint8_t *ddr, volatile uint8_t *dPort, volatile uint8_t *readR): ddr(ddr), dPort(dPort), readR(readR) {}
	PortData() {}
} PortData;
/* Pin_h */

#endif