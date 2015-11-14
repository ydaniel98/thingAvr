#ifndef LCD8_h
#define LCD8_h

#include <avr/io.h>
#include "Pin.h"
#include "PortDirect.h"

/* This struct will change depending on the LCD
settings given by the define settings staments -- TODO */
typedef struct lcd8Data {
	Pin rW;						// Read/Write select
	Pin rS;						// LCD S Register
	Pin e;						// Enable
	PortDirect dataPort;		// Port used to control the lcd

	lcd8Data(){}
	lcd8Data(Pin rW, Pin rS, Pin e, PortDirect dataPort): rW(rW), rS(rS), e(e), dataPort(dataPort) {};

}lcd8Data;

class LCD8 {
public:
	void putc(uint8_t c);					// Sends a character to the LCD
	void putCmd(uint8_t command);			// Sends a command to the LCD
	void puts(const char *s);				// Sends a string to the LCD

	void clear();							// Clears the screen of the LCD
	void setup();							// LCD Init
	void reset();							// LCD reset
	void on();								// Turns LCD on (Display)
	void off();								// Turns LCD off (Display)
	void entryMode();						// Puts LCD in entry mode

	void cursor(uint8_t c);					// Moves cursor according to the given position (RAW)
	void gotox(uint8_t x);					// Moves cursor to a given x (Position in line)
	void gotoy(uint8_t y);					// Moves cursor to a given y (Line)
	void gotoxy(uint8_t x, uint8_t y);		// Moves cursor to a given x and y (Position in line, Line)

	uint8_t x, y;							// (x, y) for LCD

	LCD8(lcd8Data _pinData_);
	LCD8(Pin rW, Pin rS, Pin e, PortDirect dataPort);

private:
	lcd8Data pinData;
	void ready();							// Checks if LCD is busy
	void signal(bool willRead);
};

#endif
