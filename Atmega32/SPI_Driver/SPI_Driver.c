/*
 * SPI_Driver.c
 *
 * Created: 12/21/2016 4:59:48 PM
 *  Author: salah yousef
 */ 


#include <avr/io.h>
#include "SPI_Driver.h"
#include <avr/interrupt.h>
unsigned char FLAG,x,FLAG2;
void SPI_MasterInit(SPI *Param_SPI)
{
	// Set MOSI and SCK and SS output
	DD_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	// set SPCR register
	SPCR |= (Param_SPI->SPIINTERRUPT<<SPIE)|(Param_SPI->SPIEnable<<SPE)|(Param_SPI->DataOrder<<DORD)|(Param_SPI->MasterSlaveSelect<<MSTR)|(Param_SPI->SPIMode<<CPHA)|(Param_SPI->SCKRate<<SPR0);
	SPSR |= Param_SPI->DoubleSpeed<<SPI2X;
	if(Param_SPI->SPIINTERRUPT==1)
		{
			sei();
			FLAG2=1;
		}
	else
			FLAG2=2;

}

void SPI_SlaveInit(SPI *Param_SPI)
{
	// Set MISO output
	DD_SPI = (1<<DD_MISO);
	// set SPCR register
	SPCR |= (Param_SPI->SPIINTERRUPT<<SPIE)|(Param_SPI->SPIEnable<<SPE)|(Param_SPI->DataOrder<<DORD)|(Param_SPI->MasterSlaveSelect<<MSTR)|(Param_SPI->SPIMode<<CPHA);
	SPSR |= Param_SPI->DoubleSpeed<<SPI2X;
	if(Param_SPI->SPIINTERRUPT==1)
		{
			sei();
			FLAG=1;
		}
	else 
		FLAG=2;
}

char spi_tranceiver (unsigned char data)
{
	
	if (FLAG2==1)
	{
		SPDR=data;
		return SPDR;	
	}
	else if (FLAG2==2)
	{
		SPDR=data;
		while(!(SPSR & (1<<SPIF)));
		return SPDR;
	}
	else if (FLAG==1)
	{
		x = data;
		return SPDR;
	}
	else //if (FLAG==2)
	{
		SPDR=data;
		while(!(SPSR & (1<<SPIF)));
		return SPDR;
	}
	
}

ISR(SPI_STC_vect)
{
	if (FLAG==1)
	{
		SPDR=x;
	}
	
}