#ifndef lcd8_c
#define lcd8_c

#include <avr/io.h>
#include <util/delay.h>
#include "lcd8.h"

void lcd8Putc(uint8_t c) {

	lcd8WaitBusy();				// Wait until not busy

	_CHAR_WRITE_MODE_();		// Set the ldc in write mode
	LCD_PORT = c;				// Set value on port

	lcd8WriteData();			// Write data to the lcd
	
	if (x != (LCD_X ))
		x++;
	if (x > (LCD_X - 1) && y != (LCD_Y - 1)) {
		x = 0;
		lcd8Gotoy(y + 1);
	}
}

void lcd8PutCmd(uint8_t command) {
	lcd8WaitBusy();				// Wait until not busy
	
	_CMD_WRITE_MODE_();			// Set the lcd in write mode
	LCD_PORT = command;			// Set value on port

	lcd8WriteData();			// Write data to the lcd
}

void lcd8Puts(const char *s) {
	while (*s) {
		lcd8Putc(*s++);
	}
}			

void lcd8Clear() {
	lcd8PutCmd(0x01);
	x = 0;
	y = 0;
}	

void lcd8Setup() {
	
	OUT(DDR_E, E);
	OUT(DDR_RW, RW);
	OUT(DDR_RS, RS);
	LCD_DDR = 0xFF;

	lcd8PutCmd(LCD_RESET);
	_delay_ms(10);
	lcd8PutCmd(LCD_RESET);
	_delay_us(200);
	lcd8PutCmd(LCD_RESET);
	_delay_us(200);

	lcd8PutCmd(LCD_FUNCTION_SET_8);
	_delay_us(50);

	lcd8PutCmd(LCD_DISPLAY_OFF);
	_delay_us(50);
	
	lcd8Clear();
	_delay_ms(2);

	lcd8PutCmd(LCD_ENTRY_MODE);
	_delay_us(50);

	lcd8PutCmd(LCD_DISPLAY_ON);
	_delay_us(50);
}												

void lcd8Cursor(uint8_t c) {
	lcd8PutCmd(LCD_CURSOR | c);
}	

void lcd8Gotox(uint8_t _x_) {
	lcd8Gotoxy(_x_, y);
}

void lcd8Gotoy(uint8_t _y_) {
	lcd8Gotoxy(x, _y_);
}	

void lcd8Gotoxy(uint8_t _x_, uint8_t _y_) {
	if (_x_ > (LCD_X - 1))
		_x_ = LCD_X;
	if (_y_ > (LCD_Y - 1))
		_y_ = LCD_Y;
	if (_y_ != y)
		x = 0;
		
	x = _x_;
	y = _y_;
	
	lcd8Cursor((_y_ << 6) + _x_);
}

void lcd8WaitBusy() {

	_READ_MODE_();				// Set lcd in read mode

	do {
		lcd8WriteData();		// 'Write Data to the lcd' -- E (low) E (high), acknowledge.
	} while(LCD_READ == 0x80);	// Wait until Lcd8 returns 0x00

	LCD_DDR = 0xFF; 			// Set LCD_PORT as output
}

void lcd8WriteData() {
	_E_HIGH_();

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

	_E_LOW_();
}


#endif