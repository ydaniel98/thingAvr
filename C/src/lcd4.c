#ifndef lcd4_c
#define lcd4_c

#include <avr/io.h>
#include <util/delay.h>
#include "lcd4.h"

void lcd4Putc(uint8_t c) {
	lcd4WaitBusy();
	
	_CHAR_WRITE_MODE_();
	
	_LCD_PORT_WRITE_(((c & 0xF0) >> 4));
	lcd4WriteData();
	
	_LCD_PORT_WRITE_((c & 0x0F));
	lcd4WriteData();
	
	_LCD_PORT_WRITE_(0x00);
	
	if (x != (LCD_X ))
	x++;
	if (x > (LCD_X - 1) && y != (LCD_Y - 1)) {
		x = 0;
		lcd4Gotoy(y + 1);
	}
}

void lcd4PutCmd(uint8_t command) {
	
	lcd4WaitBusy();
	
	_CMD_WRITE_MODE_();
	
	_LCD_PORT_WRITE_(((command & 0xF0) >> 4));
	lcd4WriteData();
	
	_LCD_PORT_WRITE_((command & 0x0F));
	lcd4WriteData();
	
	_LCD_PORT_WRITE_(0x00);
}

void lcd4Puts(const char *s) {
	while (*s) {
		lcd4Putc(*s++);
	}
}			

void lcd4Clear() {
	lcd4PutCmd(0x01);
	x = 0;
	y = 0;
}	

void lcd4Setup() {
	
	OUT(DDR_E, E);
	OUT(DDR_RW, RW);
	OUT(DDR_RS, RS);
	LCD_DDR |= LCD_MASK;
	
	lcd4NibbleCmd(LCD_RESET >> 4);
	_delay_ms(10);
	lcd4NibbleCmd(LCD_RESET >> 4);
	_delay_ms(200);
	lcd4NibbleCmd(LCD_RESET >> 4);
	_delay_ms(200);
	
	lcd4NibbleCmd(0x02);
	_delay_ms(200);
	
	lcd4PutCmd(LCD_FUNCTION_SET_4);
	_delay_us(100);
	
	lcd4PutCmd(LCD_DISPLAY_OFF);
	_delay_us(50);
	
	lcd4Clear();
	
	lcd4PutCmd(LCD_ENTRY_MODE);
	_delay_us(50);
	
	lcd4PutCmd(LCD_DISPLAY_ON);
	_delay_us(50);
	
}	

void lcd4NibbleCmd(uint8_t c) {
	_CMD_WRITE_MODE_();
	
	_E_HIGH_();
	_LCD_PORT_WRITE_((c & 0x0F));
	lcd4Wait();
	_E_LOW_();
	
	_LCD_PORT_WRITE_(0x00);
	
}

void lcd4Cursor(uint8_t c) {
	lcd4PutCmd(LCD_CURSOR | c);
}	

void lcd4Gotox(uint8_t _x_) {
	lcd4Gotoxy(_x_, y);
}

void lcd4Gotoy(uint8_t _y_) {
	lcd4Gotoxy(x, _y_);
}	

void lcd4Gotoxy(uint8_t _x_, uint8_t _y_) {
	if (_x_ > (LCD_X - 1))
		_x_ = LCD_X;
	if (_y_ > (LCD_Y - 1))
		_y_ = LCD_Y;
	if (_y_ != y)
		x = 0;
		
	x = _x_;
	y = _y_;
	
	lcd4Cursor((_y_ << 6) + _x_);
}

void lcd4WaitBusy() {
	_READ_MODE_();
	
	uint8_t flag;
	
	do {
		_E_HIGH_();
		lcd4Wait();
		flag = _LCD_PORT_READ_() << 4;
		_E_LOW_();
		
		_E_HIGH_();
		flag |= _LCD_PORT_READ_();
		_E_LOW_();
	} while(flag == 0x80);
	
	LCD_DDR |= LCD_MASK;
}

void lcd4Wait() {
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

void lcd4WriteData() {
	_E_HIGH_();
	lcd4Wait();
	_E_LOW_();
}


#endif