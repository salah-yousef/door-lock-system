/*
 * RTC.c
 *
 * Created: 1/20/2017 3:57:32 PM
 *  Author: salah
 */ 

#include <avr/io.h>
#include "RTC.h"
#include "twi.h"
extern unsigned char hour, mint, second, day, month, year;

void RTC_Set_Time()   
     {
	TWIStart(); 		// transmit START condition
	TWIWrite(0xD0); 	// address DS1307 for write
	TWIWrite(0); 		// set register pointer to 0
	TWIWrite(second);  	// set seconds
	TWIWrite(mint); 	// set minuts
	TWIWrite(hour);  	// set Hours
    TWIStop(); 
      }
void RTC_Set_Date()
        {
	TWIStart(); 		// transmit START condition
	TWIWrite(0xD0);       // address DS1307 for write
	TWIWrite(0x04); 	// set register pointer to 4
	TWIWrite(day);  	// set day
	TWIWrite(month); 	// set month
	TWIWrite(year);  	// set year
    TWIStop(); 
          }
void  RTC_Get_Time()
{
	TWIStart () ;         //transmit START condition
	TWIWrite(0xD0);       //address DS1307 for write
	TWIWrite(0);          //set register pointer to 0
	TWIStart () ; 		//transmit START condition
	TWIWrite(0xD1); 	//address DS1307 for read
	second = TWIReadACK();	//read second, return ACK
	mint = TWIReadACK();	//read minute, return ACK
	hour = TWIReadNACK();	//read hour, return NACK
    TWIStop();
	      }	//transmit STOP condition
void  RTC_Get_Date()
 {
	TWIStart () ;         //transmit START condition
	TWIWrite(0xD0);       //address DS1307 for write
	TWIWrite(4);          //set register pointer to 4
	TWIStart () ; 		//transmit START condition
	TWIWrite(0xD1); 	//address DS1307 for read
	day = TWIReadACK();	//read second, return ACK
	month = TWIReadACK();	//read minute, return ACK
	year = TWIReadNACK();	//read hour, return NACK
    TWIStop();   
	    }	//transmit STOP condition
