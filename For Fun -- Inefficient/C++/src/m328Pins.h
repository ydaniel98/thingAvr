#ifndef m328Pins_h
#define m328Pins_h

#include <avr/io.h>
#include "Pin.h"
#include "Port.h"
#include "structs.h"

#ifdef PORTD_PINS

static  PortData portDData(&DDRD, &PORTD, &PIND);

static Port portD(portDData);

#endif

#ifdef PORTB_PINS

static  PortData portBData(&DDRB, &PORTB, &PINB);

static Port portB(portBData);

#endif

#ifdef PORTC_PINS 

static PortData portCData(&DDRC, &PORTC, &PINC);

static Port portC(portCData);

#endif


#endif
