/*
 * keypad.c
 *
 * Created: 11/25/2016 3:03:00 PM
 *  Author: Kareem A.Abdullah
 */ 
#include "keypad.h"

//the keypad map
const uint8_t keypad_Characters[4][4] = {{'1','2','3','A'},
					 {'4','5','6','B'},
					 {'7','8','9','C'},
					 {127,'0',13,'D'}};

#ifdef USE_TM4C123GH6PM
	static void vKeyPadTM4C123GPinsInit(void);
#endif


#ifdef USE_TM4C123GH6PM
static void vKeyPadTM4C123GPinsInit(void)
{
	// configure the microprocessor pins for the ROWS
	SYSCTL->RCGCGPIO      |= (1U<<ROW0_PORT_GATE);
	ROW0_PORT_BASE->LOCK = 0x4C4F434B;
	ROW0_PORT_BASE->CR  |= (1U<<ROW0);
	ROW0_PORT_BASE->AFSEL &=~ (1U<<ROW0);
	ROW0_PORT_BASE->DEN |= (1U<<ROW0);
	
	SYSCTL->RCGCGPIO      |= (1U<<ROW1_PORT_GATE);
	ROW1_PORT_BASE->LOCK = 0x4C4F434B;
	ROW1_PORT_BASE->CR  |= (1U<<ROW1);
	ROW1_PORT_BASE->AFSEL &=~ (1U<<ROW1);
	ROW1_PORT_BASE->DEN |= (1U<<ROW1);
	
	SYSCTL->RCGCGPIO      |= (1U<<ROW2_PORT_GATE);
	ROW2_PORT_BASE->LOCK = 0x4C4F434B;
	ROW2_PORT_BASE->CR  |= (1U<<ROW2);
	ROW2_PORT_BASE->AFSEL &=~ (1U<<ROW2);
	ROW2_PORT_BASE->DEN |= (1U<<ROW2);
	
	SYSCTL->RCGCGPIO      |= (1U<<ROW3_PORT_GATE);
	ROW3_PORT_BASE->LOCK = 0x4C4F434B;
	ROW3_PORT_BASE->CR  |= (1U<<ROW3);
	ROW3_PORT_BASE->AFSEL &=~ (1U<<ROW3);
	ROW3_PORT_BASE->DEN |= (1U<<ROW3);
	// configure the microprocessor pins for the LINES
	SYSCTL->RCGCGPIO      |= (1U<<LINE0_PORT_GATE);
	LINE0_PORT_BASE->LOCK     = 0x4C4F434B;
	LINE0_PORT_BASE->CR      |= (1U<<LINE0);
	LINE0_PORT_BASE->AFSEL   &=~(1U<<LINE0);
	LINE0_PORT_BASE->DEN     |= (1U<<LINE0);
        LINE0_PORT_BASE->PUR     |= (1U<<LINE0);
	
	SYSCTL->RCGCGPIO      |= (1U<<LINE1_PORT_GATE);
	LINE1_PORT_BASE->LOCK     = 0x4C4F434B;
	LINE1_PORT_BASE->CR      |= (1U<<LINE1);
	LINE1_PORT_BASE->AFSEL   &=~(1U<<LINE1);
	LINE1_PORT_BASE->DEN     |= (1U<<LINE1);
        LINE1_PORT_BASE->PUR     |= (1U<<LINE1);
	
	SYSCTL->RCGCGPIO     |= (1U<<LINE2_PORT_GATE);
	LINE2_PORT_BASE->LOCK     = 0x4C4F434B;
	LINE2_PORT_BASE->CR      |= (1U<<LINE2);
	LINE2_PORT_BASE->AFSEL   &=~(1U<<LINE2);
	LINE2_PORT_BASE->DEN     |= (1U<<LINE2);
        LINE2_PORT_BASE->PUR     |= (1U<<LINE2);

	SYSCTL->RCGCGPIO     |= (1U<<LINE3_PORT_GATE);
	LINE3_PORT_BASE->LOCK     = 0x4C4F434B;
	LINE3_PORT_BASE->CR      |= (1U<<LINE3);
	LINE3_PORT_BASE->AFSEL   &=~(1U<<LINE3);
	LINE3_PORT_BASE->DEN     |= (1U<<LINE3);
        LINE3_PORT_BASE->PUR     |= (1U<<LINE3);
}
#endif

void vKeypadInit (void)
{
	#ifdef USE_TM4C123GH6PM
		vKeyPadTM4C123GPinsInit();
	#endif
        
        
                // set Rows direction as output.
                ROW0_DDR |= (1U << ROW0);
                ROW1_DDR |= (1U << ROW1);
                ROW2_DDR |= (1U << ROW2);
                ROW3_DDR |= (1U << ROW3);
                // set Lines direction as input.
                LINE0_DDR &=~ (1U << LINE0);
                LINE1_DDR &=~ (1U << LINE1);
                LINE2_DDR &=~ (1U << LINE2);
                LINE3_DDR &=~ (1U << LINE3);
                // connect Lines to pull up.
                LINE0_PULLUP |= (1U << LINE0);
                LINE1_PULLUP |= (1U << LINE1);
                LINE2_PULLUP |= (1U << LINE2);
                LINE3_PULLUP |= (1U << LINE3);
        
}

uint8_t ucKeypadScan(void)
{
	// loop the output on rows.
	uint8_t row,line=0,input;
        for (row=0 ; row <4 ; row++)
	{
		// Set all rows to high.
		ROW0_PORT |= (1U << ROW0);
		ROW1_PORT |= (1U << ROW1);
		ROW2_PORT |= (1U << ROW2);
		ROW3_PORT |= (1U << ROW3);
		// Clear the numbered row.
		switch (row)
			{
				case 0: ROW0_PORT &=~ (1U << ROW0); break;
				case 1: ROW1_PORT &=~ (1U << ROW1);	break;
				case 2: ROW2_PORT &=~ (1U << ROW2);	break;
				case 3: ROW3_PORT &=~ (1U << ROW3);	break;
			}
		// Check if the user has hit a keypad button
		if ((ALL_LINES) != 1)
			{
                                         // Read the input.
                                          input  = (((LINE0_PIN & (1U << LINE0))>>LINE0)<<4);	
                                          input |= (((LINE1_PIN & (1U << LINE1))>>LINE1)<<5);	
                                          input |= (((LINE2_PIN & (1U << LINE2))>>LINE2)<<6);	
                                          input |= (((LINE3_PIN & (1U << LINE3))>>LINE3)<<7);	
                                          // Switch input and set the specific line.
                                          switch (input)
                                          	{
                                          		case 0xE0 : line = 0; break;	// input = 0b 1110 0000
                                          		case 0xD0 : line = 1; break;	// input = 0b 1101 0000
                                          		case 0xB0 : line = 2; break;	// input = 0b 1011 0000
                                          		case 0x70 : line = 3; break;	// input = 0b 0111 0000
                                          	}
                                          // Wait till the user release his finger.
                                          while (ALL_LINES != 1);
                                          break;
                                          
                                     
			}
	}
	// Check if no input entered.
	if (row == 4)
		{
			return NO_KEY_PRESSED;
		}
	// Return the array character.
	return keypad_Characters[row][line]; 
}