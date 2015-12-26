#ifndef timeInfo_h
#define timeInfo_h

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


#endif