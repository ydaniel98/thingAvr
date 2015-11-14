#ifndef Display_h
#define Display_h

#include <avr/io.h>
#include "PortVirtual.h"
#include "Pin.h"

/* Holds the data for a 4bit 7segment display decoder */
typedef struct decoder4BitMap {
	Pin a;
	Pin b; 
	Pin c;
	Pin d;
	
	decoder4BitMap(Pin a, Pin b, Pin c, Pin d): a(a), b(b), c(c), d(d) {}
	decoder4BitMap() {}
	
}decoder4bitMap;
/* Display_h */


/* Class definition - Display controll, assuming the use a decoder */
class Display: PortVirtual {
public:
	void write(uint32_t w);					// Writes the given number to the display as long as it is within the digit range
	void clearDisp();						// Writes 0 to the display
	void test();							// Writes 8 to all displays
	void overflowDisp();					// Writes 9 t0 all displays

	Display(decoder4bitMap *_decodMap_, uint8_t _digits_);

private:
	decoder4bitMap *decodMap;				// List for pins regarding the displays
	Pin portBuffer[4];						// Buffer for the virtual port
	uint8_t digits;							// Digits - Amount of displays connected to micro controller
	uint8_t parse[10];						// List that holds the result from parseInt (Used in write to get the digits from the input num)
	uint32_t lastWrite;						// Guard to avoid writing the same number twice

	void setBuffer(decoder4bitMap dc4M);	// Sets the buffer for the virtual port
	void update(uint8_t digitUpdatePoint);	// Updates the displays - Sets them to zero ( The ones that are not reached by the range of the numeber)
};

#endif