#ifndef rtClock_h
#define rtClock_h

#include <avr/io.h>
#include <2wire.h>

/* RTC I2C Address */
#define RT_CLOCK_ADDR 0x68
/*******************/

/* Memory Addresses */
#define _SS_ADDR_	0x00		// Seconds Address
#define _MM_ADDR_	0x01		// Minutes Address
#define _HH_ADDR_	0x02		// Hours   Address
#define _DD_ADDR_	0x03		// Day     Address
#define _D_ADDR_	0x04		// Date    Address
#define _M_ADDR_	0x05		// Month   Address
#define _Y_ADDR_	0x06		// Year	   Address
/********************/

/* Error code variable */
uint8_t rtClockErrCode;

//	1	-> All Nominal
//  0	-> Failed (General)

//	2	-> Failed getting seconds
//	3	-> Failed getting minutes
//	4	-> Failed getting hours
//	5	-> Failed getting day
//	6	-> Failed getting date
//	7	-> Failed getting month
//	8	-> Failed getting year

//  9	-> Failed setting seconds
//  10	-> Failed setting minutes
//  11	-> Failed setting hours
//  12	-> Failed setting day
//  13	-> Failed setting date
//  14	-> Failed setting month
//  15	-> Failed setting year

/************************/

/* Definitions for error codes */
#define RT_CLOCK_NOMINAL		1
#define RT_CLOCK_F_GENERAL		0

#define RT_CLOCK_F_G_SS			2
#define RT_CLOCK_F_G_MM			3
#define RT_CLOCK_F_G_HH			4
#define RT_CLOCK_F_G_DD			5
#define RT_CLOCK_F_G_D			6
#define RT_CLOCK_F_G_M			7
#define RT_CLOCK_F_G_Y			8

#define RT_CLOCK_F_S_SS			9
#define RT_CLOCK_F_S_MM			10
#define RT_CLOCK_F_S_HH			11
#define RT_CLOCK_F_S_DD			12
#define RT_CLOCK_F_S_D			13
#define RT_CLOCK_F_S_M			14
#define RT_CLOCK_F_S_Y			15
/*************************************************/

#define _RT_CLOCK_GET_VALUE_(M_VALUE)	(M_VALUE - (6  * (M_VALUE >> 4)))
#define _RT_CLOCK_GET_M_VALUE_(VALUE)	(VALUE + (6 * (VALUE / 10)))

#define _RT_CLOCK_GET_ITEM(M_ADDR, BUFFER, ERROR) \
				rtClockErrCode = ERROR; \
				if (!tWireStart()) \
					return 0; \
				if (!tWireRequest(RT_CLOCK_ADDR, M_ADDR)) \
					return 0; \
				if (!tWireReadBus(BUFFER)) \
					return 0; \
 				rtClockErrCode = RT_CLOCK_NOMINAL; \
				tWireNack(); \
				tWireEnd();	\
 				return _RT_CLOCK_GET_VALUE_(BUFFER[0])

#define _RT_CLOCK_WRITE_ITEM(DATA, ERROR) \
				if (!tWireWriteA(RT_CLOCK_ADDR, DATA, 2)) { \
					rtClockErrCode = ERROR; \
					return; \
				} \
				rtClockErrCode = RT_CLOCK_NOMINAL

/*
* Write to the RTC
*/

void rtClockSetSS(uint8_t ss);
void rtClockSetMM(uint8_t mm);
void rtClockSetHH(uint8_t hh);
// void rtClockSetTimeInfo(timeInfo tI);

void rtClockSetDD(uint8_t dd);
void rtClockSetD(uint8_t d);
void rtClockSetM(uint8_t m);
void rtClockSetY(uint8_t y);
// void rtClockSetDateInfo(dateInfo dI);

/**/

void rtClockSetup();

/*
* Read from the RTC
*/

uint8_t rtClockGetSS();
uint8_t rtClockGetMM();
uint8_t rtClockGetHH();
// void rtClockGetTimeInfo(timeInfo * tI);

uint8_t rtClockGetDD();
uint8_t rtClockGetD();
uint8_t rtClockGetM();
uint8_t rtClockGetY();
// void rtClockGetDateInfo(dateInfo * dI);

/**/

#endif
