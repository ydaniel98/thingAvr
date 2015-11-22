#ifndef lcd8_cpp
#define lcd8_cpp

#include <avr/io.h>
#include <util/delay.h>
#include "lcd8.h"
#include "lcdDefs.h"
#include "convenience.h"

#define CHAR_WRITE_MODE	pinData.rW.low(); pinData.rS.high();	

#define CMD_WRITE_MODE  pinData.rW.low(); pinData.rS.low();	

#define READ_MODE		pinData.dataPort.clear(); pinData.dataPort.mode(INPUT); pinData.rS.low(); pinData.rW.high();						

#define WRITE_DATA		pinData.e.low(); signal(false);	pinData.dataPort.clear();	


/****************************************************/
/* Constructors 									*/
/****************************************************/

Lcd8::Lcd8(Pin rW, Pin rS, Pin e, Port dataPort) {
	pinData = lcd8Data(rW, rS, e, dataPort);	
}

Lcd8::Lcd8(lcd8Data _pinData_): pinData(_pinData_) {

	pinData.rS.mode(OUTPUT);			// RS pin in output mode
	pinData.e.mode(OUTPUT);				// Enable pin in output mode
	pinData.rW.mode(OUTPUT);			// R/W pin in output mode
	pinData.dataPort.mode(OUTPUT);		// Set the port in output mode

	x = 0; 								// Make sure x is 0
	y = 0;								// Make sure y is 0
}

/***************************************************/

void Lcd8::setup() {

	putCmd(LCD_RESET);
	_delay_ms(10);
	putCmd(LCD_RESET);
	_delay_us(200);
	putCmd(LCD_RESET);
	_delay_us(200);

	putCmd(LCD_FUNCTION_SET_8);
	_delay_us(50);

	putCmd(LCD_DISPLAY_OFF);
	_delay_us(50);
	
	clear();

	putCmd(LCD_ENTRY_MODE);
	_delay_us(50);

	putCmd(LCD_DISPLAY_ON);
	_delay_us(50);
}

void Lcd8::putc(uint8_t c) {

	ready();						// Wait until Lcd8 is not busy
	pinData.dataPort.set(c);		// Set the data in the port
	CHAR_WRITE_MODE
	WRITE_DATA
}	

void Lcd8::putCmd(uint8_t command) {

	ready();							// Wait until Lcd8 is not busy
	pinData.dataPort.set(command);		// Set the data in the port
	CMD_WRITE_MODE
	WRITE_DATA
}

void Lcd8::ready() {

	READ_MODE

	while(pinData.dataPort.read() == 0x80)			// Wait until Lcd8 returns 0x00
		signal(true);

	pinData.dataPort.mode(OUTPUT);
}	

void Lcd8::signal(bool willRead) {

	pinData.e.high();				// Set the enable Pin High
	if (willRead)
		__asm__ volatile("nop");	// Extra delay when reading

	/* Delay depending on the clock rate */
#	if F_CPU > 4000000UL
	_delay_ms(0.5);
# 	else
#	if F_CPU > 1000000UL
	__asm__ volatile("nop");
#	if F_CPU > 2000000UL
	__asm__ volatile("nop");
	__asm__ volatile("nop");
#	endif
#	endif
#	endif
	/************************************/

	pinData.e.low();				// Set the enable pin low
}	

void Lcd8::clear() {
	putCmd(0x01);
	_delay_ms(2);
}	

void Lcd8::cursor(uint8_t c) {
	putCmd(LCD_CURSOR | c);
}

void Lcd8::gotoxy(uint8_t _x_, uint8_t _y_) {
	x = _x_; 
	y = _y_;

	cursor((_y_ << 6) + _x_);
}

void Lcd8::gotox(uint8_t _x_) {
	gotoxy(_x_, y);
}

void Lcd8::gotoy(uint8_t _y_) {
	gotoxy(x, _y_);
}

void Lcd8::puts(const char *s) {
	while (*s)
		putc(*s++);
}

void Lcd8::puts(const char *s, uint8_t param) {
	switch (param) {
		case AUTO: {
			uint8_t pos = 0;
			while (*s) {
				if (pos == LCD_X) 
					gotoy(y + 1, GUARD);
				putc(*s++);
				pos++;
			}
			return;
		}
		case CLEAR: {
			clear();
			gotoxy(0, 0);
			break;
		}
	}
	puts(s);
}

void Lcd8::gotox(uint8_t _x_, bool guard) {
	gotoxy(_x_, y, guard);
}

void Lcd8::gotoy(uint8_t _y_, bool guard) {
	gotoxy(x, _y_, guard);
}

void Lcd8::gotoxy(uint8_t _x_, uint8_t _y_, bool guard) {
	if (guard) {
		if (_x_ < LCD_X && _y_ < LCD_Y)
			gotoxy(_x_, _y_);
	}
}

#endif














