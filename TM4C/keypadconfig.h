/*
 * keypadconfig.h
 *
 * Created: 11/25/2016 3:06:10 PM
 *  Author: Kareem A.Abdullah
 */ 

#ifndef KEYPADCONFIG_H_
#define KEYPADCONFIG_H_

//uncomment your Target
//#define USE_ATMEGA32
#define USE_TM4C123GH6PM


#ifndef USE_ATMEGA32
#ifndef USE_TM4C123GH6PM
	#error "your target is not defined. available targets are: USE_ATMEGA32 or USE_TM4C123GH6PM"
#endif
#endif


#ifdef USE_ATMEGA32
#ifdef USE_TM4C123GH6PM
	#error "USE_ATMEGA32 and USE_TM4C123GH6PM are both defined"
#endif
#endif


#ifdef USE_ATMEGA32
	#define F_CPU	8000000UL
	#include <avr/io.h>
	#include <util/delay.h>
#endif

#ifdef USE_TM4C123GH6PM
	#define F_CPU	16000000UL
	#include "TM4C123GH6PM.h"
	#include "delay.h"
#endif

#include <stdint.h>
/**************************************************************************
-----------                   ----------
|TM4C123GH6PM|                |   Keypad    |
|           |                 |          |
|        PB3|---------------->|Row0        |
|        PC4|---------------->|Row1        |
|        PC5|---------------->|Row2        |
|        PC6|---------------->|Row3        |                                        |
|        PC7|---------------->|Line0        |
|        PD6|---------------->|Line1        |
|        PD7|---------------->|Line2        |
|        PF4|---------------->|Line3                                |
-----------                   ----------
***************************************************************************/
#ifdef USE_TM4C123GH6PM
	
	#define  PORTA_GATE_PIN          0
	#define  PORTB_GATE_PIN          1
	#define  PORTC_GATE_PIN          2
	#define  PORTD_GATE_PIN          3
	#define  PORTE_GATE_PIN          4
	#define  PORTF_GATE_PIN          5
	

	#define ROW0_PORT_GATE        PORTB_GATE_PIN
	#define ROW0_PORT_BASE        GPIOB
	
	#define ROW1_PORT_GATE        PORTE_GATE_PIN
	#define ROW1_PORT_BASE        GPIOE
	
	#define ROW2_PORT_GATE        PORTF_GATE_PIN
	#define ROW2_PORT_BASE        GPIOF
	
	#define ROW3_PORT_GATE        PORTD_GATE_PIN
	#define ROW3_PORT_BASE        GPIOD

	#define LINE0_PORT_GATE       PORTD_GATE_PIN
	#define LINE0_PORT_BASE       GPIOD
	
	#define LINE1_PORT_GATE       PORTF_GATE_PIN
	#define LINE1_PORT_BASE       GPIOF
	
	#define LINE2_PORT_GATE       PORTB_GATE_PIN
	#define LINE2_PORT_BASE       GPIOB
	
	#define LINE3_PORT_GATE       PORTE_GATE_PIN
	#define LINE3_PORT_BASE       GPIOE

#endif


#define ROW0			2
#define ROW0_DDR		(GPIOB->DIR)
#define ROW0_PORT		(GPIOB->DATA)

#define ROW1			0
#define ROW1_DDR		(GPIOE->DIR)
#define ROW1_PORT		(GPIOE->DATA)

#define ROW2			0
#define ROW2_DDR		(GPIOF->DIR)
#define ROW2_PORT		(GPIOF->DATA)

#define ROW3			6
#define ROW3_DDR		(GPIOD->DIR)
#define ROW3_PORT		(GPIOD->DATA)

#define LINE0			7
#define LINE0_DDR		(GPIOD->DIR)
#define LINE0_PIN		(GPIOD->DATA)
#define LINE0_PULLUP	        (GPIOD->DATA)

#define LINE1			4
#define LINE1_DDR		(GPIOF->DIR)
#define LINE1_PIN		(GPIOF->DATA)
#define LINE1_PULLUP	        (GPIOF->DATA)

#define LINE2			3
#define LINE2_DDR		(GPIOB->DIR)
#define LINE2_PIN		(GPIOB->DATA)
#define LINE2_PULLUP	        (GPIOB->DATA)

#define LINE3			1
#define LINE3_DDR		(GPIOE->DIR)
#define LINE3_PIN		(GPIOE->DATA)
#define LINE3_PULLUP	        (GPIOE->DATA)


#endif /* KEYPADCONFIG_H_ */