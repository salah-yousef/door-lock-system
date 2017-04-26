/*
 * keypad.h
 *
 * Created: 11/25/2016 3:00:32 PM
 *  Author: Kareem A.Abdullah
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "keypadconfig.h"

#define NO_KEY_PRESSED		0

void vKeypadInit (void);
uint8_t ucKeypadScan(void);

#define ALL_LINES			(((LINE0_PIN & (1U << LINE0))>>LINE0)\
					&((LINE1_PIN & (1U << LINE1))>>LINE1)\
					&((LINE2_PIN & (1U << LINE2))>>LINE2)\
					&((LINE3_PIN & (1U << LINE3))>>LINE3))

#endif /* KEYPAD_H_ */