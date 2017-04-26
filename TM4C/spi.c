#include "spi.h"

void spi_init(void)
{
    //  To enable and initialize the SSI, the following steps are necessary:
      //1. Enable the SSI module using the RCGCSSI register (see page 346).
          SYSCTL->RCGCSSI = (1U<<3 );
          
      //2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 340).
          SYSCTL->RCGCGPIO = (1U<<3);
    //To find out which GPIO port to enable, refer to Table 23-5 on page 1351.
      //3. Set the GPIO AFSEL bits for the appropriate pins (see page 671). To determine which GPIOs to
      //configure, see Table 23-4 on page 1344.
          GPIOD->AFSEL |= (1U<<0)|(1U<<1)|(1U<<2)|(1U<<3);
          
      //4. Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate
      //pins. See page 688 and Table 23-5 on page 1351.
          GPIOD->PCTL |= (1<<0)|(1<<4)|(1<<8)|(1<<12);
      //5. Program the GPIODEN register to enable the pin's digital function. In addition, the drive strength,
      //drain select and pull-up/pull-down functions must be configured. Refer to “General-Purpose
      //Input/Outputs (GPIOs)” on page 649 for more information.
      //Note: Pull-ups can be used to avoid unnecessary toggles on the SSI pins, which can take the
      //slave to a wrong state. In addition, if the SSIClk signal is programmed to steady state
      //High through the SPO bit in the SSICR0 register, then software must also configure the
      //GPIO port pin corresponding to the SSInClk signal as a pull-up in the GPIO Pull-Up
      //Select (GPIOPUR) register.
          GPIOD->DEN |= (1U<<0)|(1U<<1)|(1U<<2)|(1U<<3);
    //For each of the frame formats, the SSI is configured using the following steps:
      //1. Ensure that the SSE bit in the SSICR1 register is clear before making any configuration changes.
          SSI3->CR1 &=~ (1U<<1);
      //2. Select whether the SSI is a master or slave:
      //a. For master operations, set the SSICR1 register to 0x0000.0000.
      //b. For slave mode (output enabled), set the SSICR1 register to 0x0000.0004.
      //c. For slave mode (output disabled), set the SSICR1 register to 0x0000.000C.
          SSI3->CR1 = 0x00000000;
      //3. Configure the SSI clock source by writing to the SSICC register.
          SSI3->CC = 0x00;
      //4. Configure the clock prescale divisor by writing the SSICPSR register.
          SSI3->CPSR = 10;
      //5. Write the SSICR0 register with the following configuration:
      //? Serial clock rate (SCR)
      //? Desired clock phase/polarity, if using Freescale SPI mode (SPH and SPO)
      //? The protocol mode: Freescale SPI, TI SSF, MICROWIRE (FRF)
      //? The data size (DSS)
          SSI3->CR0 = (0x7<<0);
    //6. Optionally, configure the SSI module for ?DMA use with the following steps:
      //a. Configure a ?DMA for SSI use. See “Micro Direct Memory Access (?DMA)” on page 585 for
      //more information.
      //b. Enable the SSI Module's TX FIFO or RX FIFO by setting the TXDMAE or RXDMAE bit in the
      //SSIDMACTL register.
    //7. Enable the SSI by setting the SSE bit in the SSICR1 register.
        SSI3->CR1 |=(1<<1); 
      //As an example, assume the SSI must be configured to operate with the following parameters:
      //? Master operation
      //? Freescale SPI mode (SPO=1, SPH=1)
      //? 1 Mbps bit rate
      //? 8 data bits
      //Assuming the system clock is 20 MHz, the bit rate calculation would be:
      //SSInClk = SysClk / (CPSDVSR * (1 + SCR))
      //1x106 = 20x106 / (CPSDVSR * (1 + SCR))
      //In this case, if CPSDVSR=0x2, SCR must be 0x9.
      //The configuration sequence would be as follows:
      //1. Ensure that the SSE bit in the SSICR1 register is clear.
      //2. Write the SSICR1 register with a value of 0x0000.0000.
      //3. Write the SSICPSR register with a value of 0x0000.0002.
      //4. Write the SSICR0 register with a value of 0x0000.09C7.
      //5. The SSI is then enabled by setting the SSE bit in the SSICR1 register.
      //  
}
 /**********************************************************************************/
    uint8_t spi_tranceiver(uint8_t data)
 {
    SSI3->DR = data;
    while ( (SSI3->SR & (1<<0) ) ==0);
    return SSI3->DR ;
 }