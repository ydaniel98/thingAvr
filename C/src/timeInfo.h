#ifndef timeInfo_h
#define timeInfo_h

#include <avr/io.h>

/* Data data string constants */
// const char MONTHS[12][3] = {
// 	"Jan",
// 	"Feb",
// 	"Mar",
// 	"Apr",
// 	"May",
// 	"Jun",
// 	"Jul",
// 	"Aug",
// 	"Sep",
// 	"Oct",
// 	"Nov",
// 	"Dec"
// };
// 
// const char DAYS[7][3] = {
// 	"Sun",
// 	"Mon",
// 	"Tue",
// 	"Web",
// 	"Thu",
// 	"Fri",
// 	"Sat"
// };
/******************************/

/* Info on time (seconds, minutes, hours) */
typedef struct timeInfo {
	uint8_t ss;			// Seconds 
	uint8_t mm;			// Minutes
	uint8_t hh;			// Hours
}timeInfo;
/******************************************/

/* Info on time (days, month, year) */
typedef struct dateInfo {
	timeInfo now;		// Current time 
	uint8_t dd;			// Day
	uint8_t d;			// Date
	uint8_t m;			// Month
	uint8_t y;			// Year
}dateInfo;
/************************************/

/* Utils */
uint8_t time24ToTime12(uint8_t time24);
uint8_t time12ToTime24(uint8_t time12, uint8_t am);

void getClockString(timeInfo t, char * buffer, uint8_t s);
void getClockString12(timeInfo t, char * buffer, uint8_t s);

void twoDigitString(uint8_t n, uint8_t * buffer);
void timeInfoFromClockString(const char * s, timeInfo *t);

uint8_t numberFromTwoDigit(uint8_t d1, uint8_t d2);

void timeInfoFromClockString12(const char * buffer, timeInfo *t);
/*********/


#endif