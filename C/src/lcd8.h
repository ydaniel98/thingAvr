#ifndef lcd8_h 
#define lcd8_h

#include "io_s.h"

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

#ifndef LCD_FUNCTION_SET_8
#define LCD_FUNCTION_SET_8 	0x38
#endif

/**************************/	

#define DDR_E					DDRB
#define PORT_E					PORTB
#define E						PINB2

#define DDR_RS					DDRB
#define PORT_RS					PORTB
#define RS						PINB0

#define DDR_RW					DDRB
#define PORT_RW					PORTB
#define RW						PINB1

#define LCD_PORT				PORTD
#define LCD_DDR					DDRD
#define LCD_READ				PIND

#define _E_HIGH_() 				HIGH(PORT_E, E)
#define _E_LOW_() 				LOW(PORT_E, E)

#define _RS_HIGH_() 			HIGH(PORT_RS, RS)
#define _RS_LOW_() 				LOW(PORT_RS, RS)

#define _RW_HIGH_() 			HIGH(PORT_RW, RW)
#define _RW_LOW_()				LOW(PORT_RW, RW)

#define _CHAR_WRITE_MODE_() 	_RW_LOW_(); _RS_HIGH_()
#define _CMD_WRITE_MODE_()		_RW_LOW_(); _RS_LOW_()

#define _READ_MODE_()			LCD_PORT = 0x00; LCD_DDR = 0x00; _RS_LOW_(); _RW_HIGH_()

void lcd8Putc(uint8_t c);											// Sends a character to the LCD
void lcd8PutCmd(uint8_t command);									// Sends a command to the LCD
void lcd8Puts(const char *s);										// Sends a string to the LCD

void lcd8Clear();													// Clears the screen of the LCD
void lcd8Setup();													// LCD Init

void lcd8Cursor(uint8_t c);											// Moves cursor according to the given position (RAW)
void lcd8Gotox(uint8_t _x_);										// Moves cursor to a given x (Position in line)
void lcd8Gotoy(uint8_t _y_);										// Moves cursor to a given y (Line)
void lcd8Gotoxy(uint8_t _x_, uint8_t _y_);							// Moves cursor to a given x and y (Position in line, Line)

void lcd8WaitBusy();												// Waits until the busy flag is cleared 
void lcd8WriteData();												// Writes data to the lcd

uint8_t x, y;														// Variables to keep track of the position in the lcd 


#endif















