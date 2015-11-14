#ifndef m328Pins_h
#define m328Pins_h

#include <avr/io.h>
#include "Pin.h"

#ifdef PORTD_PINS

static  PortData portDData(&DDRD, &PORTD, &PIND);

static  Pin pD0(portDData, PD0);
static  Pin pD1(portDData, PD1);
static  Pin pD2(portDData, PD2);
static  Pin pD3(portDData, PD3);
static  Pin pD4(portDData, PD4);
static  Pin pD5(portDData, PD5);
static  Pin pD6(portDData, PD6);
static  Pin pD7(portDData, PD7);

#endif

#ifdef PORTB_PINS

static  PortData portBData(&DDRB, &PORTB, &PINB);

static  Pin pB0(portBData, PB0);
static  Pin pB1(portBData, PB1);
static  Pin pB2(portBData, PB2);
static  Pin pB3(portBData, PB3);
static  Pin pB4(portBData, PB4);
static  Pin pB5(portBData, PB5);
static  Pin pB6(portBData, PB6);
static  Pin pB7(portBData, PB7);

#endif


#endif