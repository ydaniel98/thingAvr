#ifndef m328Pins_h
#define m328Pins_h

#include <avr/io.h>
#include "Pin.h"

#ifdef PORTD_PINS

static  PortData portDData(&DDRD, &PORTD, &PIND);

static  Pin pD0(portDData, PIND0);
static  Pin pD1(portDData, PIND1);
static  Pin pD2(portDData, PIND2);
static  Pin pD3(portDData, PIND3);
static  Pin pD4(portDData, PIND4);
static  Pin pD5(portDData, PIND5);
static  Pin pD6(portDData, PIND6);
static  Pin pD7(portDData, PIND7);

#endif

#ifdef PORTB_PINS

static  PortData portBData(&DDRB, &PORTB, &PINB);

static  Pin pB0(portBData, PINB0);
static  Pin pB1(portBData, PINB1);
static  Pin pB2(portBData, PINB2);
static  Pin pB3(portBData, PINB3);
static  Pin pB4(portBData, PINB4);
static  Pin pB5(portBData, PINB5);
static  Pin pB6(portBData, PINB6);
static  Pin pB7(portBData, PINB7);

#endif


#endif
