#ifndef timeInfo_c
#define timeInfo_c

#include "timeInfo.h"
#include <avr/io.h>

/* Utils */
uint8_t time24ToTime12(uint8_t time24) {
	if (!time24)
		return 12;
	if (time24 < 13)
		return time24;
	return time24 - 12;
}

void twoDigitString(uint8_t n, uint8_t * buffer) {
	buffer[1] = (n % 10) + '0';
	buffer[0] = ((n - (n % 10)) / 10) + '0';
	buffer[2] = '\0';
}

uint8_t numberFromTwoDigit(uint8_t d1, uint8_t d2) {
	return ((d1 - '0') * 10) + (d2 - '0');
}

void timeInfoFromClockString(const char * s, timeInfo *t) {
	t->hh = numberFromTwoDigit(s[0], s[1]);
	t->mm = numberFromTwoDigit(s[3], s[4]);
	t->ss = numberFromTwoDigit(s[6], s[7]);
}

void getClockString(timeInfo t, char * buffer, uint8_t s) {
	uint8_t numBuffer[3];
	if (s < 9)
	return;
	twoDigitString(t.hh, numBuffer);
	buffer[0] = numBuffer[0];
	buffer[1] = numBuffer[1];
	
	buffer[2] = ':';
	
	twoDigitString(t.mm, numBuffer);
	buffer[3] = numBuffer[0];
	buffer[4] = numBuffer[1];

	buffer[5] = ':';
	
	twoDigitString(t.ss, numBuffer);
	buffer[6] = numBuffer[0];
	buffer[7] = numBuffer[1];
	
	buffer[8] = '\0';
}

void getClockString12(timeInfo t, char * buffer, uint8_t s) {
	if (s < 12)
	return;
	
	uint8_t am = 1;
	if (t.hh > 12)
	am = 0;
	
	t.hh = time24ToTime12(t.hh);
	getClockString(t, buffer, s);
	
	buffer[8] = ' ';
	
	if (am)
	buffer[9]  = 'A';
	else
	buffer[9]  = 'P';
	
	buffer[10] = 'M';
	buffer[11] = '\0';
}

uint8_t time12ToTime24(uint8_t time12, uint8_t am) {
	return (time12 % 12) + (am ? 0 : 12);
}

void timeInfoFromClockString12(const char * buffer, timeInfo *t) {
	timeInfoFromClockString(buffer, t);
	t->hh = time12ToTime24(numberFromTwoDigit(buffer[0], buffer[1]), buffer[9] == 'A');
}

/*********/

#endif