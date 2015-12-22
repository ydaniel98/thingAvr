#ifndef analog_h
#define analog_h

#include <avr/io.h>

#define ANALOG_SETUP(AREF, DIV_FACTOR) ADMUX = AREF; ADCSRA = DIV_FACTOR

#define ADC_DIV_FACTOR_2	0x80
#define ADC_DIV_FACTOR_4	0x82
#define ADC_DIV_FACTOR_8	0x82
#define ADC_DIV_FACTOR_16	0x83
#define ADC_DIV_FACTOR_32	0x84
#define ADC_DIV_FACTOR_64	0x85
#define ADC_DIV_FACTOR_128	0x86

#define ADC_AREF		0x00
#define ADC_VCC			0x40
#define ADC_INTERN_AVCC 0xC0

#define PWM_FAST 0x03
#define PWM_PHASE_CORRECT 0x01

#define A 0x80
#define B 0x20
#define NONE 0x00

#define PWM_WRITE(PWM_R, NUM) PWM_R = NUM
#define PWM_SETUP(TIMER_RA, TIMER_RB, PIN_ENABLE1, PIN_ENABLE2, M) TIMER_RA |= M | PIN_ENABLE1 | PIN_ENABLE2; TIMER_RB |= (1 << CS00)

uint16_t analogRead(uint8_t channel);																									// Reads the value in the given analog channel

#endif









