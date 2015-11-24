#ifndef lcd8_c
#define lcd8_c

#include <avr/io.h>
#include <util/delay.h>
#include "lcd8.h"
#include "lcdDefs.h"

void lcd8Putc(uint8_t c) {

	lcd8WaitBusy();				// Wait until not busy

	LCD_PORT = c;				// Set value on port

	_CHAR_WRITE_MODE_();		// Set the ldc in write mode

	lcd8WriteData();			// Write data to the lcd
}

void lcd8PutCmd(uint8_t command) {
	lcd8WaitBusy();				// Wait until not busy

	LCD_PORT = c;				// Set value on port

	_CMD_WRITE_MODE_();			// Set the ldc in write mode

	lcd8WriteData();			// Write data to the lcd
}

void lcd8Puts(const char *s) {

}

void lcd8Puts(const char *s, uint8_t param) {

}				

void lcd8Clear() {

}	

void lcd8Setup() {

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
	
	clear();

	lcd8PutCmd(LCD_ENTRY_MODE);
	_delay_us(50);

	lcd8PutCmd(LCD_DISPLAY_ON);
	_delay_us(50);
}												

void lcd8Cursor(uint8_t c) {

}	

void lcd8Gotox(uint8_t _x_) {

}

void lcd8Gotoy(uint8_t _y_) {

}	

void lcd8Gotox(uint8_t _x_, bool guard) {

}	

void lcd8Gotoy(uint8_t _y_, bool guard) {

}	

void lcd8Gotoxy(uint8_t _x_, uint8_t _y_) {

}

void lcd8Gotoxy(uint8_t _x_, uint8_t _y_, bool guard) {

}

void lcd8WaitBusy() {

	_READ_MODE_();				// Set lcd in read mode

	while(LCD_PORT == 0x80)		// Wait until Lcd8 returns 0x00
		lcd8WriteData();		// 'Write Data to the lcd' -- E (low) E (high), acknowledge.

	LCD_PORT = 0xFF; 			// Set LCD_PORT as output
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