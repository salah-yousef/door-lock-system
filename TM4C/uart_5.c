#include "uart_5.h"  

void uart_init_5(uint32_t baudrate,uint32_t f_cpu)
{
  float brd,temp; 
  //1. Enable the UART module using the RCGCUART register (see page 344).
          SYSCTL->RCGCUART |= (1<<5);
     //2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 340).
     //To find out which GPIO port to enable, refer to Table 23-5 on page 1351.
          SYSCTL->RCGCGPIO |= (1<<4);
     //3. Set the GPIO AFSEL bits for the appropriate pins (see page 671). To determine which GPIOs to
     //configure, see Table 23-4 on page 1344.
          GPIOE->AFSEL |= (1<<4)|(1<<5);
     //4. Configure the GPIO current level and/or slew rate as specified for the mode selected (see
     //page 673 and page 681).
     //902 June 12, 2014
     //Texas Instruments-Production Data
     //Universal Asynchronous Receivers/Transmitters (UARTs)
     //5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate
     //pins (see page 688 and Table 23-5 on page 1351).
          GPIOE->PCTL  |= (1<<16)|(1<<20);
          GPIOE->DEN  |= (1<<4)|(1<<5);
     //To use the UART, the peripheral clock must be enabled by setting the appropriate bit in the
     //RCGCUART register (page 344). In addition, the clock to the appropriate GPIO module must be
     //enabled via the RCGCGPIO register (page 340) in the System Control module. To find out which
     //GPIO port to enable, refer to Table 23-5 on page 1351.
     //This section discusses the steps that are required to use a UART module. For this example, the
     //UART clock is assumed to be 20 MHz, and the desired UART configuration is:
     //¦ 115200 baud rate
     //¦ Data length of 8 bits
     //¦ One stop bit
     //¦ No parity
     //¦ FIFOs disabled
     //¦ No interrupts
     //The first thing to consider when programming the UART is the baud-rate divisor (BRD), because
     //the UARTIBRD and UARTFBRD registers must be written before the UARTLCRH register. Using
     //the equation described in “Baud-Rate Generation” on page 896, the BRD can be calculated:
     //BRD = 16,000,000 / (16 * 9600) = 104.166667
          brd = (float)f_cpu / (16 * baudrate);
          temp = (float)brd - (uint32_t)brd;

     //which means that the DIVINT field of the UARTIBRD register (see page 914) should be set to 10
     //decimal or 0xA. The value to be loaded into the UARTFBRD register (see page 915) is calculated
     //by the equation:
     //UARTFBRD[DIVFRAC] = integer(0.166667 * 64 + 0.5) = 11
     //With the BRD values in hand, the UART configuration is written to the module in the following order:
     //1. Disable the UART by clearing the UARTEN bit in the UARTCTL register.
          UART5->CTL &=~ (1<<0);
     //2. Write the integer portion of the BRD to the UARTIBRD register.
          UART5->IBRD = (uint32_t)brd;
     //3. Write the fractional portion of the BRD to the UARTFBRD register.
          UART5->FBRD = (uint32_t)(((float)temp * 64 )+ 0.5);
     //4. Write the desired serial parameters to the UARTLCRH register (in this case, a value of
     //0x0000.0060).
          UART5->LCRH = (0x3<<5);
     //5. Configure the UART clock source by writing to the UARTCC register.
          UART5->CC = 0x0;
     //6. Optionally, configure the µDMA channel (see “Micro Direct Memory Access (µDMA)” on page 585)
     //and enable the DMA option(s) in the UARTDMACTL register.
     //7. Enable the UART by setting the UARTEN bit in the UARTCTL register.
          UART5->CTL |=(1U<<0)|(1U<<8)|(1U<<9);
     
}
 void UART_Write_5(uint8_t ch)
{
  while((UART5->FR & (1U<<5))!=0);  /* wait for transmitter buffer to be free*/
  UART5->DR = ch;
}
uint8_t UART_Read_5(void)
{
  char data;
  while((UART5->FR & (1U<<4))!=0);  /* wait for reciever buffer to have data*/
  data = UART5->DR;
  return data;
}

void uart_write_string_5(char const * string)
{
  while(*string != '\0')
  {
    UART_Write_5(*string);
    string++;
  }
}

void uart_write_int_5(uint32_t number)
{
  uint16_t length = snprintf( NULL, 0, "%d", number );
  char* str = malloc( length + 1 );
  snprintf( str, length + 1, "%d", number );
  free(str);
  uart_write_string_5(str);
}
