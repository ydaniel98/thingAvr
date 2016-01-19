#ifndef lcd4_h 
#define lcd4_h

#include "io_s.h"
#include <avr/io.h>
#include <stdlib.h>

/* Commands for lcd init */

#ifndef LCD_RESET
#define LCD_RESET 			0x30
#endif

#ifndef LCD_DISPLAY_OFF
#define LCD_DISPLAY_OFF	 	0x08
#endif

#ifndef LCD_DISPLAY_ON
#define LCD_DISPLAY_ON 		0x0C
#endif

#ifndef LCD_ENTRY_MODE
#define LCD_ENTRY_MODE 		0x06
#endif	

#ifndef LCD_CURSOR
#define LCD_CURSOR 			0x80
#endif

#ifndef LCD_X
#define LCD_X 				0x10
#endif			

#ifndef LCD_Y
#define LCD_Y 				0x02
#endif

#ifndef LCD_FUNCTION_SET_4
#define LCD_FUNCTION_SET_4 	0x28
#endif

/**************************/	

#define DDR_E					DDRB
#define PORT_E					PORTB
#define E						PINB4

#define DDR_RS					DDRB
#define PORT_RS					PORTB
#define RS						PINB5

#define DDR_RW					DDRC
#define PORT_RW					PORTC
#define RW						PINC1

#define LCD_PORT				PORTB
#define LCD_DDR					DDRB
#define LCD_READ				PINB
#define LCD_MASK				0x0F
#define LCD_SHIFT				0

#define _E_HIGH_() 				HIGH(PORT_E, E)
#define _E_LOW_() 				LOW(PORT_E, E)

#define _RS_HIGH_() 			HIGH(PORT_RS, RS)
#define _RS_LOW_() 				LOW(PORT_RS, RS)

#define _RW_HIGH_() 			HIGH(PORT_RW, RW)
#define _RW_LOW_()				LOW(PORT_RW, RW)

#define _CHAR_WRITE_MODE_() 	_RW_LOW_(); _RS_HIGH_()
#define _CMD_WRITE_MODE_()		_RW_LOW_(); _RS_LOW_()

#define _LCD_PORT_WRITE_(NUM)	WRITE_BITS(NUM, LCD_PORT, LCD_SHIFT, LCD_MASK)
#define _LCD_PORT_READ_()		READ_BITS(LCD_READ, LCD_SHIFT, LCD_MASK)

#define _READ_MODE_()			_LCD_PORT_WRITE_(0x00); LCD_DDR &= ~(LCD_MASK); _RS_LOW_(); _RW_HIGH_()

#define _LCD_POS_GUARD()		if (x > (LCD_X - 1) && y != (LCD_Y - 1)) lcd4Gotoy(y + 1)

void lcd4NibbleCmd(uint8_t c);										// Sends the lower nibble to the LCD
void lcd4Putc(uint8_t c);											// Sends a character to the LCD
void lcd4PutCmd(uint8_t command);									// Sends a command to the LCD
void lcd4Puts(const char *s);										// Sends a string to the LCD

void lcd4Clear();													// Clears the screen of the LCD
void lcd4Setup();													// LCD Init

void lcd4Cursor(uint8_t c);											// Moves cursor according to the given position (RAW)
void lcd4Gotox(uint8_t _x_);										// Moves cursor to a given x (Position in line)
void lcd4Gotoy(uint8_t _y_);										// Moves cursor to a given y (Line)
void lcd4Gotoxy(uint8_t _x_, uint8_t _y_);							// Moves cursor to a given x and y (Position in line, Line)

void lcd4WaitBusy();												// Waits until the busy flag is cleared 
void lcd4WriteData();												// Writes data to the lcd
void lcd4Wait();

void lcd4Putn(int num, uint8_t radix);								// Writes a number to the lcd
void lcd4PutcA(uint8_t c);											// Writes a number but goes to the next line if necessary
void lcd4ClearRange(uint8_t s, uint8_t f);							// Clears the range specified

void lcd4SetRange(uint8_t s, uint8_t f, uint8_t c);					// Sets a character in the given range

uint8_t x, y;														// Variables to keep track of the position in the lcd 


#endif















