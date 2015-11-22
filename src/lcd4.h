#ifndef lcd4_h
#define lcd4_h

#include <avr/io.h>
#include "lcdDefs.h"
#include "Pin.h"
#include "PinGroup.h"

typedef struct lcd4Data {
	Pin rW;
	Pin rS;
	Pin e;

	PinGroup dataPort;

	lcd4Data() {}
	lcd4Data(Pin rW, Pin rS, Pin e, PinGroup dataPort): rW(rW), rS(rS), e(e), dataPort(dataPort) {};

}lcd4Data;

class Lcd4 {
public:

	void putc(uint8_t c);												// Sends a character to the LCD
	void putCmd(uint8_t command);										// Sends a command to the LCD
	void puts(const char *s);											// Sends a string to the LCD
	void puts(const char *s, uint8_t param);							// Sends a string to the LCD and changes line automaticly if specified

	void clear();														// Clears the screen of the LCD
	void setup();														// LCD Init

	void cursor(uint8_t c);												// Moves cursor according to the given position (RAW)
	void gotox(uint8_t _x_);											// Moves cursor to a given x (Position in line)
	void gotoy(uint8_t _y_);											// Moves cursor to a given y (Line)
	void gotox(uint8_t _x_, bool guard);								// Extra guard parameter
	void gotoy(uint8_t _y_, bool guard);								// Extra guard paramenter
	void gotoxy(uint8_t _x_, uint8_t _y_);								// Moves cursor to a given x and y (Position in line, Line)
	void gotoxy(uint8_t _x_, uint8_t _y_, bool guard);					// Makeds sure that data in lcd does not go beyond it's bounds

	uint8_t x, y;														// (x, y) for LCD

	void nibbleCmd(uint8_t n); 											// Writes the lower nibble command to the lcd

	Lcd4() {}
	Lcd4(lcd4Data pinData);
	Lcd4(Pin rW, Pin rS, Pin e, PinGroup dataPort);

private:
	Pin rW;
	Pin rS;
	Pin e;

	PinGroup dataPort;

	void signal(bool willRead);
	void ready();
	void wait(bool willRead);
};

#endif