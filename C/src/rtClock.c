#ifndef rtClock_c
#define rtClock_c

#include <avr/io.h>
#include <2wire.h>
#include <rtClock.h>


void rtClockSetup() {
	rtClockSetSS(rtClockGetSS());		// Echo seconds to check RTC and set an error if necessary
}

/* Write to the RTC */

	/* Time Info */
void rtClockSetSS(uint8_t ss) {
	if (ss > 59)
		ss = 59;
	uint8_t data[2] = {_SS_ADDR_, _RT_CLOCK_GET_M_VALUE_(ss)};
	_RT_CLOCK_WRITE_ITEM(data, RT_CLOCK_F_G_SS);
}

void rtClockSetMM(uint8_t mm) {
	if (mm > 59)
		mm = 59;
	uint8_t data[2] = {_MM_ADDR_, _RT_CLOCK_GET_M_VALUE_(mm)};
	_RT_CLOCK_WRITE_ITEM(data, RT_CLOCK_F_G_MM);
}

void rtClockSetHH(uint8_t hh) {
	if (hh > 23)
		hh = 23;
	uint8_t data[2] = {_HH_ADDR_, _RT_CLOCK_GET_M_VALUE_(hh)};
	_RT_CLOCK_WRITE_ITEM(data, RT_CLOCK_F_G_HH);
}

void rtClockSetTimeInfo(timeInfo tI) {
	rtClockSetSS(tI.ss);
	rtClockSetMM(tI.mm);
	rtClockSetHH(tI.hh);
}

	/*************/

	/* Date Info */
void rtClockSetDD(uint8_t dd) {
	if (dd > 7)
		dd = 7;
	if (dd < 1)
		dd = 1;
	uint8_t data[2] = {_DD_ADDR_, _RT_CLOCK_GET_M_VALUE_(dd)};
	_RT_CLOCK_WRITE_ITEM(data, RT_CLOCK_F_G_DD);
}

void rtClockSetD(uint8_t d) {
	if (d > 31)
		d = 31;
	if (d < 1)
		d = 1;
	uint8_t data[2] = {_D_ADDR_, _RT_CLOCK_GET_M_VALUE_(d)};
	_RT_CLOCK_WRITE_ITEM(data, RT_CLOCK_F_G_D);
}

void rtClockSetM(uint8_t m) {
	if (m > 12)
		m = 12;
	if (m < 1)
		m = 1;
	uint8_t data[2] = {_M_ADDR_, _RT_CLOCK_GET_M_VALUE_(m)};
	_RT_CLOCK_WRITE_ITEM(data, RT_CLOCK_F_G_M);
}

void rtClockSetY(uint8_t y) {
	if (y > 99)
		y = 99;
	uint8_t data[2] = {_Y_ADDR_, _RT_CLOCK_GET_M_VALUE_(y)};
	_RT_CLOCK_WRITE_ITEM(data, RT_CLOCK_F_G_Y);
}

void rtClockSetDateInfo(dateInfo dI) {
	rtClockSetTimeInfo(dI.now);
	rtClockSetDD(dI.dd);
	rtClockSetD(dI.d);
	rtClockSetM(dI.m);
	rtClockSetY(dI.y);
}
	/*************/

/********************/

/* Read from the RTC */

	/* Time Info */
uint8_t rtClockGetSS() {
	uint8_t ss[1];
	_RT_CLOCK_GET_ITEM(_SS_ADDR_, ss, RT_CLOCK_F_G_SS);
}

uint8_t rtClockGetMM() {
	uint8_t mm[1];
	_RT_CLOCK_GET_ITEM(_MM_ADDR_, mm, RT_CLOCK_F_G_MM);
}

uint8_t rtClockGetHH() {
	uint8_t hh[1];
	_RT_CLOCK_GET_ITEM(_HH_ADDR_, hh, RT_CLOCK_F_G_HH);
}

void rtClockGetTimeInfo(timeInfo * tI) {
	errCode = 0;
	
	tI->ss = rtClockGetSS();
	tI->mm = rtClockGetMM();
	tI->hh = rtClockGetHH();
	
	if (errCode != 0)
		errCode = -1;
}
	/* Time Info */

	/* Date Info */
uint8_t rtClockGetDD() {
	uint8_t dd[1];
	_RT_CLOCK_GET_ITEM(_DD_ADDR_, dd, RT_CLOCK_F_G_DD);
}

uint8_t rtClockGetD() {
	uint8_t d[1];
	_RT_CLOCK_GET_ITEM(_D_ADDR_, d, RT_CLOCK_F_G_D);
}

uint8_t rtClockGetM() {
	uint8_t m[1];
	_RT_CLOCK_GET_ITEM(_M_ADDR_, m, RT_CLOCK_F_G_M);
}

uint8_t rtClockGetY() {
	uint8_t y[1];
	_RT_CLOCK_GET_ITEM(_Y_ADDR_, y, RT_CLOCK_F_G_Y);
}

void rtClockGetDateInfo(dateInfo * dI) {
	errCode = 0;
	
	rtClockGetTimeInfo(&(dI->now));
	
	dI->dd = rtClockGetDD();
	dI->d  = rtClockGetD();
	dI->m  = rtClockGetM();
	dI->y  = rtClockGetY(); 
	
	if (errCode != 0)
		errCode = -1;
}
	/*************/

/********************/

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
	uint8_t am = 1;
	if (t.hh > 12)
		am = 0;
		
	if (s < 12)
		return;
		
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
/*********/

#endif