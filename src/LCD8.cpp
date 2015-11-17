#ifndef LCD8_cpp
#define LCD8_cpp

#include <avr/io.h>
#include <util/delay.h>
#include "LCD8.h"
#include "convenience.h"


/****************************************************/
/* Constructors 									*/
/****************************************************/

LCD8::LCD8(Pin rW, Pin rS, Pin e, PortDirect dataPort) {
	pinData = lcd8Data(rW, rS, e, dataPort);	
}

LCD8::LCD8(lcd8Data _pinData_): pinData(_pinData_) {

	pinData.rS.mode(OUTPUT);			// RS pin in output mode
	pinData.e.mode(OUTPUT);				// Enable pin in output mode
	pinData.rW.mode(OUTPUT);			// R/W pin in output mode
	pinData.dataPort.mode(OUTPUT);		// Set the port in output mode

	x = 0; 								// Make sure x is 0
	y = 0;								// Make sure y is 0
}

/***************************************************/

void LCD8::setup() {
	reset();
	_delay_ms(9.8);
	reset();
	reset();

	/* Enable 8bit mode in LCD8 */
	putCmd(0x38);
	_delay_us(50);
	/**************************/

	off();
	clear();
	entryMode();
	on();
}

void LCD8::putc(uint8_t c) {

	ready();						// Wait until LCD8 is not busy
	pinData.dataPort.set(c);		// Set the data in the port
	pinData.rW.low();				// Set the R/W low
	pinData.rS.high();				// Set the RS pin high
	pinData.e.low();				// Set the Enable pin initially low
	signal(false);					// Signal (Flash) the enable pin
	pinData.dataPort.clear();		// Clear data from the port
}	

void LCD8::putCmd(uint8_t command) {

	ready();							// Wait until LCD8 is not busy
	pinData.dataPort.set(command);		// Set the data in the port
	pinData.rW.low();					// Set the R/W pin low
	pinData.rS.low();					// Set the RS pin low
	pinData.e.low();					// Set the enable pin initially low
	signal(false);						// Signal the enable pin
	pinData.dataPort.clear();			// Clear data from port
}

void LCD8::ready() {

	pinData.dataPort.clear();						// Make sure data port is clear
	pinData.dataPort.mode(INPUT);					// Change port to input mode

	pinData.rS.low();								// Set RS pin low		
	pinData.rW.high();								// Set R/W high

	while(pinData.dataPort.read() == 0x80)			// Wait until LCD8 returns 0x00
		signal(true);

	pinData.dataPort.mode(OUTPUT);
}	

void LCD8::signal(bool willRead) {

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

void LCD8::clear() {
	putCmd(0x01);
	_delay_ms(2);
}	

void LCD8::reset() {
	putCmd(LCD_RESET);
	_delay_us(200);
}

void LCD8::off() {
	putCmd(LCD_DISPLAY_OFF);
	_delay_us(50);
}

void LCD8::entryMode() {
	putCmd(LCD_ENTRY_MODE);
	_delay_us(50);
}

void LCD8::on() {
	putCmd(LCD_DISPLAY_ON);
	_delay_us(50);
}

void LCD8::cursor(uint8_t c) {
	putCmd(LCD_CURSOR | c);
}

void LCD8::gotoxy(uint8_t _x_, uint8_t _y_) {
	x = _x_; 
	y = _y_;

	cursor((_y_ << 6) + _x_);
}

void LCD8::gotox(uint8_t _x_) {
	gotoxy(_x_, y);
}

void LCD8::gotoy(uint8_t _y_) {
	gotoxy(x, _y_);
}

void LCD8::puts(const char *s) {
	while (*s)
		putc(*s++);
}

void LCD8::puts(const char *s, bool autocLineChange) {
	if (autocLineChange) {
		uint8_t pos = 0;
		while (*s) {
			if (pos == LCD_X) 
				gotoy(y + 1, GUARD);
			putc(*s++);
			pos++;
		}
		return;
	}
	puts(s);
}

void LCD8::gotox(uint8_t _x_, bool guard) {
	gotoxy(_x_, y, guard);
}

void LCD8::gotoy(uint8_t _y_, bool guard) {
	gotoxy(x, _y_, guard);
}

void LCD8::gotoxy(uint8_t _x_, uint8_t _y_, bool guard) {
	if (guard) {
		if (_x_ < LCD_X && _y_ < LCD_Y)
			gotoxy(_x_, _y_);
	}
}

void LCD8::puts(const char *s, bool autocLineChange, bool willClear) {
	if (willClear) {
		clear();
		gotoxy(0, 0);
	}
	if (autocLineChange) {
		puts(s, autocLineChange);
		return;
	}
	puts(s);

}

#endif














