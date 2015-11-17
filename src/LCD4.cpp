#ifndef LCD4_cpp
#define LCD4_cpp

#include <avr/io.h>
#include <util/delay.h>
#include "LCD4.h"
#include "convenience.h"

/****************************************************/
/* Constructors 									*/
/****************************************************/

LCD4::LCD4(Pin rW, Pin rS, Pin e, PortVirtual dataPort) {
	pinData = lcd4Data(rW, rS, e, dataPort);	
}

LCD4::LCD4(lcd4Data _pinData_): pinData(_pinData_) {

	pinData.rS.mode(OUTPUT);			// RS pin in output mode
	pinData.e.mode(OUTPUT);				// Enable pin in output mode
	pinData.rW.mode(OUTPUT);			// R/W pin in output mode
	pinData.dataPort.mode(OUTPUT);		// Set the port in output mode

	x = 0; 								// Make sure x is 0
	y = 0;								// Make sure y is 0
}

/***************************************************/

void LCD4::setup() {
	pinData.rS.low();
	pinData.rW.low();

	pinData.e.low();

	pinData.dataPort.set(3);

	signal(false);

	_delay_ms(50);
	signal(false);
	_delay_ms(50);
	signal(false);
	_delay_ms(50);

	pinData.dataPort.set(2);
	signal(false);
	_delay_ms(50);

	putCmd(0x28);
	_delay_ms(50);

	off();
	clear();
	entryMode();
	on();
}

void LCD4::putc(uint8_t c) {

	ready();
	pinData.dataPort.set((c & 0xF0) >> 4);

	pinData.rS.high();
	pinData.rW.low();
	pinData.e.low();

	signal(true);

	pinData.dataPort.set(c & 0x0F);
	signal(true);

	pinData.dataPort.clear();
}	

void LCD4::putCmd(uint8_t command) {

	ready();
	pinData.dataPort.set((command & 0xF0) >> 4);

	pinData.rS.low();
	pinData.rW.low();
	pinData.e.low();

	signal(false);

	pinData.dataPort.set(command & 0x0F);
	signal(false);

	pinData.dataPort.clear();
}

void LCD4::ready() {

	uint8_t status = 0x80;

	pinData.dataPort.mode(INPUT);
	pinData.rS.low();
	pinData.rW.high();

	while(status & 0x80) {
		signal(true);
		status = pinData.dataPort.read() << 4;
		signal(true);
		status += pinData.dataPort.read();
	}
	pinData.dataPort.mode(OUTPUT);
}	

void LCD4::signal(bool willRead) {

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

void LCD4::clear() {
	putCmd(0x01);
	_delay_ms(2);
}	

void LCD4::reset() {
	putCmd(LCD_RESET);
	_delay_us(200);
}

void LCD4::off() {
	putCmd(LCD_DISPLAY_OFF);
	_delay_us(50);
}

void LCD4::entryMode() {
	putCmd(LCD_ENTRY_MODE);
	_delay_us(50);
}

void LCD4::on() {
	putCmd(LCD_DISPLAY_ON);
	_delay_us(50);
}

void LCD4::cursor(uint8_t c) {
	putCmd(LCD_CURSOR | c);
}

void LCD4::gotoxy(uint8_t _x_, uint8_t _y_) {
	x = _x_; 
	y = _y_;

	cursor((_y_ << 6) + _x_);
}

void LCD4::gotox(uint8_t _x_) {
	gotoxy(_x_, y);
}

void LCD4::gotoy(uint8_t _y_) {
	gotoxy(x, _y_);
}

void LCD4::puts(const char *s) {
	while (*s)
		putc(*s++);
}

void LCD4::puts(const char *s, bool autocLineChange) {
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

void LCD4::gotox(uint8_t _x_, bool guard) {
	gotoxy(_x_, y, guard);
}

void LCD4::gotoy(uint8_t _y_, bool guard) {
	gotoxy(x, _y_, guard);
}

void LCD4::gotoxy(uint8_t _x_, uint8_t _y_, bool guard) {
	if (guard) {
		if (_x_ < LCD_X && _y_ < LCD_Y)
			gotoxy(_x_, _y_);
	}
}

void LCD4::puts(const char *s, bool autocLineChange, bool willClear) {
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