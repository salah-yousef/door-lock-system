#include "timer.h"


void timer_init(void)
{
//  The GPTM is configured for One-Shot and Periodic modes by the following sequence:
SYSCTL->RCGCTIMER |=(1U<<0);
//1. Ensure the timer is disabled (the TAEN bit in the GPTMCTL register is cleared) before making
  //any changes.
TIMER0->CTL &=~(1U<<TAEN);
//2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
TIMER0->CFG =  0x00000000;
//3. Configure the TAMR field in the GPTM Timer A Mode Register (GPTMTAMR):
  //a. Write a value of 0x1 for One-Shot mode.
  //b. Write a value of 0x2 for Periodic mode.
  TIMER0->TAMR |=(0x1<<TAM) ;
//4. Optionally configure the TASNAPS, TAWOT, TAMTE, and TACDIR bits in the GPTMTAMR register
  //to select whether to capture the value of the free-running timer at time-out, use an external
  //trigger to start counting, configure an additional trigger or interrupt, and count up or down.
  TIMER0->TAMR &=~(1U<<4);
//5. Load the start value into the GPTM Timer A Interval Load Register (GPTMTAILR).
  TIMER0->TAILR = 640000000U - 1;
//6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
//(GPTMIMR).

//7. Set the TAEN bit in the GPTMCTL register to enable the timer and start counting.

}
void start_timer_40s(void)
{
  TIMER0->CTL |=(1U<<TAEN);
  TIMER0->ICR |=(1U<<TATOCINT);
}
void stop_timer_40s(void)
{
  TIMER0->CTL &=~(1U<<TAEN);

}

void timer_init_2(void)
{
    //  The GPTM is configured for One-Shot and Periodic modes by the following sequence:
SYSCTL->RCGCTIMER |=(1U<<2);
//1. Ensure the timer is disabled (the TAEN bit in the GPTMCTL register is cleared) before making
  //any changes.
TIMER2->CTL &=~(1U<<TAEN);
//2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
TIMER2->CFG =  0x00000000;
//3. Configure the TAMR field in the GPTM Timer A Mode Register (GPTMTAMR):
  //a. Write a value of 0x1 for One-Shot mode.
  //b. Write a value of 0x2 for Periodic mode.
  TIMER2->TAMR |=(0x2<<TAM) ;
//4. Optionally configure the TASNAPS, TAWOT, TAMTE, and TACDIR bits in the GPTMTAMR register
  //to select whether to capture the value of the free-running timer at time-out, use an external
  //trigger to start counting, configure an additional trigger or interrupt, and count up or down.

//5. Load the start value into the GPTM Timer A Interval Load Register (GPTMTAILR).
TIMER2->TAILR = 4000000U - 1;
//6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
//(GPTMIMR).
TIMER2->IMR |=(1U<<TATOIM);
__enable_interrupt();
NVIC->ISER[0] |=(1U<<23);
//7. Set the TAEN bit in the GPTMCTL register to enable the timer and start counting.

}
