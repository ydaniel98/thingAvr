#ifndef lcd8_h 
#define lcd8_h

#include "io_s.h"

/* Input to some functions -- For the sake readability */
#ifndef AUTO
#define AUTO 				0
#endif	

#ifndef MANUAL 
#define MANUAL 				1
#endif	

#ifndef GUARD
#define GUARD 				1
#endif

#ifndef FREE 			
#define FREE 				0
#endif	

#ifndef CLEAR			
#define CLEAR				2
#endif	

#ifndef KEEP
#define KEEP 				3
#endif

/*********************************************************/

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

#ifndef LCD_FUNCTION_SET_4
#define LCD_FUNCTION_SET_4 	0x28
#endif

/**************************/	

#define _E_HIGH_() 				HIGH(DDR_E, E)
#define _E_LOW_() 				LOW(DDR_E, E)

#define _RS_HIGH_() 			HIGH(DDR_RS, RS)
#define _RS_LOW_() 				LOW(DDR_RS, RS)

#define _RW_HIGH_() 			HIGH(DDR_RW, RW)
#define _RW_LOW_()				HIGH(DDR_RW, RW)

#define _CHAR_WRITE_MODE_() 	_RW_LOW_; _RS_HIGH_;
#define _CMD_WRITE_MODE_()		_RW_LOW_; _RS_LOW_;

#define _READ_MODE_()			LCD_PORT = 0x00; LCD_DDR = 0x00; _RS_LOW_ _RW_HIGH_

void lcd8Putc(uint8_t c);											// Sends a character to the LCD
void lcd8PutCmd(uint8_t command);									// Sends a command to the LCD
void lcd8Puts(const char *s);										// Sends a string to the LCD
void lcd8Puts(const char *s, uint8_t param);						// Sends a string to the LCD and changes line automaticly if specified

void lcd8Clear();													// Clears the screen of the LCD
void lcd8Setup();													// LCD Init

void lcd8Cursor(uint8_t c);											// Moves cursor according to the given position (RAW)
void lcd8Gotox(uint8_t _x_);										// Moves cursor to a given x (Position in line)
void lcd8Gotoy(uint8_t _y_);										// Moves cursor to a given y (Line)
void lcd8Gotox(uint8_t _x_, bool guard);							// Extra guard parameter
void lcd8Gotoy(uint8_t _y_, bool guard);							// Extra guard paramenter
void lcd8Gotoxy(uint8_t _x_, uint8_t _y_);							// Moves cursor to a given x and y (Position in line, Line)
void lcd8Gotoxy(uint8_t _x_, uint8_t _y_, bool guard);				// Makeds sure that data in lcd does not go beyond it's bounds

void lcd8WaitBusy();												// Waits until the busy flag is cleared 
void lcd8WriteData();												// Writes data to the lcd

uint8_t x, y;														// Variables to keep track of the position in the lcd 


#endif















