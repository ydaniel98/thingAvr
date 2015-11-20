#ifndef lcd4_cpp
#define lcd4_cpp

#include <avr/io.h>
#include <util/delay.h>
#include "PinGroup.h"
#include "Pin.h"
#include "lcd4.h"
#include "lcdDefs.h"
#include "convenience.h"

Lcd4::Lcd4(lcd4Data pinData): rW(pinData.rW), rS(pinData.rS), e(pinData.e), dataPort(pinData.dataPort) {

	e.mode(OUTPUT);
	rS.mode(OUTPUT);
	rW.mode(OUTPUT);
	dataPort.mode(OUTPUT);

	x = 0; 
	y = 0;
}

Lcd4::Lcd4(Pin rW, Pin rS, Pin e, PinGroup dataPort): rW(rW), rS(rS), e(e), dataPort(dataPort) {
	e.mode(OUTPUT);
	rS.mode(OUTPUT);
	rW.mode(OUTPUT);
	dataPort.mode(OUTPUT);

	x = 0; 
	y = 0;
}

void Lcd4::setup() {

	nibbleCmd(LCD_RESET >> 4);
	_delay_ms(10);
	nibbleCmd(LCD_RESET >> 4);
	_delay_us(200);
	nibbleCmd(LCD_RESET >> 4);
	_delay_us(200);

	nibbleCmd(0x02);
	_delay_us(200);

	putCmd(LCD_FUNCTION_SET_4);
	_delay_us(100);

	putCmd(LCD_DISPLAY_OFF);
	_delay_us(50);
	
	clear();

	putCmd(LCD_ENTRY_MODE);
	_delay_us(50);

	putCmd(LCD_DISPLAY_ON);
	_delay_us(50);
}	

void Lcd4::putc(uint8_t c) {

	rS.high();
	rW.low();

	dataPort.set((c & 0xF0) >> 4);	//Send higher nibble
	signal(false);

	dataPort.set((c & 0x0F)); 		// Send lower nibble
	signal(false);

	dataPort.clear();
}	

void Lcd4::putCmd(uint8_t command) {

	ready();

	rS.low();
	rW.low();

	dataPort.set((command & 0xF0) >> 4); 		// Send high nibble
	signal(false);

	dataPort.set(command & 0x0F);				// Send low nibble
	signal(false);

	dataPort.clear();
}

void Lcd4::nibbleCmd(uint8_t n) {

	rS.low();
	rW.low();

	e.high();
	dataPort.set(n & 0x0F);
	wait(false);
	e.low();

	dataPort.clear();
}

void Lcd4::ready() {

	dataPort.clear();

	rS.low();
	rW.high();

	dataPort.mode(INPUT);

	while (dataPort.read() == 0x08)
		signal(true);

	dataPort.mode(OUTPUT);
}	

void Lcd4::signal(bool willRead) {

	e.high();				// Set the enable Pin High
	wait(willRead);
	e.low();				// Set the enable pin low
}	

void Lcd4::wait(bool willRead) {
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

}

void Lcd4::clear() {
	putCmd(0x01);
	_delay_ms(2);
}	

void Lcd4::cursor(uint8_t c) {
	putCmd(LCD_CURSOR | c);
}

void Lcd4::gotoxy(uint8_t _x_, uint8_t _y_) {
	x = _x_; 
	y = _y_;

	cursor((_y_ << 6) + _x_);
}

void Lcd4::gotox(uint8_t _x_) {
	gotoxy(_x_, y);
}

void Lcd4::gotoy(uint8_t _y_) {
	gotoxy(x, _y_);
}

void Lcd4::puts(const char *s) {
	while (*s)
		putc(*s++);
}

void Lcd4::puts(const char *s, bool autocLineChange) {
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

void Lcd4::gotox(uint8_t _x_, bool guard) {
	gotoxy(_x_, y, guard);
}

void Lcd4::gotoy(uint8_t _y_, bool guard) {
	gotoxy(x, _y_, guard);
}

void Lcd4::gotoxy(uint8_t _x_, uint8_t _y_, bool guard) {
	if (guard) {
		if (_x_ < LCD_X && _y_ < LCD_Y)
			gotoxy(_x_, _y_);
	}
}

void Lcd4::puts(const char *s, bool autocLineChange, bool willClear) {
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