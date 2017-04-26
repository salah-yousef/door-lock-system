/*
 * main.c
 *
 * Created: 12/21/2016 5:00:52 PM
 *  Author: salah yousef
 */ 


#include <avr/io.h>
#include <avr/eeprom.h> 
#include <avr/interrupt.h>
#define F_CPU	8000000UL
#include <util/delay.h>
#include <string.h>
#include "SPI_Driver.h"
#include "ee24c16.h"
#include "RTC.h"
#define SW0 (1U<<0)
#define buzzer (1U<<4)
#define LED0 (1U<<5)

unsigned char hour, mint, second, day, month, year;
int main(void)
{
	SPI SPI1;
	SPI1.MasterSlaveSelect=Slave;
	SPI1.SPIINTERRUPT=Disaple;
	SPI1.DoubleSpeed=Disaple;
	SPI1.SPIMode=Mode0;
	SPI1.SPIEnable=Enable;
	SPI1.DataOrder=MSB_First;	
	SPI_SlaveInit(&SPI1);
	
	
	uint8_t u8ebyte=0;
	uint8_t hihi=0;
	uint16_t i=0;
	uint16_t m=0;
	uint16_t n=0;
	uint16_t q=0;
	
	uint16_t ii=eeprom_read_word ((uint16_t*)65520);
	DDRD &= ~ SW0;
	DDRD |= buzzer;
	DDRD |= LED0;

	char buffer=0;
	char flag = 0;
	 uint8_t number[5];
	 memset(number,0,5);
	 uint16_t start =0;
	 TWIInit();
	 
     hour = 0x03; mint = 0x40 ; second = 0x00;
     RTC_Set_Time(); 	// Set time 23:58:30
     
     day = 0x13; month = 0x02 ; year = 0x17;
     RTC_Set_Date(); 	// Set date 28-01-2017
     
	 
	 
	while(1)
	{
		//TODO:: Please write your application code
		ii=eeprom_read_word ((uint16_t*)65520);
		if ((PIND&SW0)!=0)
		{
			EEWriteByte(65535, 190);
			_delay_ms(10);	
					
		}
		if (flag==0)
		{
			flag=1;
			EEReadByte(65535, &u8ebyte);
			_delay_ms(10);
			buffer=spi_tranceiver(u8ebyte);
			_delay_ms(10);
		}
		
		if (buffer=='N')
		{
			EEWriteByte(65535, 0);
			_delay_ms(10);
			for (;(i<32)&&(buffer!=1)&&(buffer!='N');i++)
			{
				EEWriteByte(i,buffer);
				_delay_ms(10);
				buffer=spi_tranceiver(0);
			}
			
		}
		
			buffer=spi_tranceiver(u8ebyte);
			
			if (buffer=='/')
			{
				spi_tranceiver(0);
				_delay_ms(10);
				spi_tranceiver(0);
				_delay_ms(10);
				
				for(i=0;i<1024;i++)
				{
					EEReadByte(i, &u8ebyte);
					spi_tranceiver(u8ebyte);
					if((i%8==0)&&(((i/8)%2)==0))
					{
						if(u8ebyte==255){
							break;
						}
					}
				}
			}
			
			
			else if (buffer=='b')
			{
				PORTD ^= buzzer ;
				PORTD ^= LED0;
				
			}
			
			
			else if (buffer=='c')
			{
				PORTD &=~ buzzer ;
				PORTD &=~ LED0;
			}
			
			else if (buffer=='d')
			{
				for (;(ii<1024)&&(buffer!=1)&&(buffer!='N');ii++)
				{
						buffer=spi_tranceiver(0);
						EEWriteByte(ii,buffer);
						_delay_ms(10);
						
				}
				eeprom_write_word ((uint16_t*)65520, ii);
			}
			
			
			else if (buffer=='e')
			{
				if(spi_tranceiver(0)=='E')
				{
						for(m=0;(m<5);m++)
						{
							number[m]=spi_tranceiver(0);
						}
						start = ((number[4]*1)+(number[3]*10)+(number[2]*100)+(number[1]*1000)+(number[0]*10000));
						
						for ((n=start),(q=0);(n<(start+16))&&(buffer!=1)&&(buffer!='N')&&(q<16);n++,q++)
						{
							buffer=spi_tranceiver(0);
							EEWriteByte(n,buffer);
							_delay_ms(10);
							
						}
			
						for ((n=start),(q=0);(n<(start+16))&&(q<16);n++,q++)
						{
							EEReadByte(n, &hihi);
									
						}
												
				}
			
			}
			
			
			
		else if (buffer=='f')
			{
				if(spi_tranceiver(0)=='E')
				{
					for(m=0;(m<5);m++)
					{
						number[m]=spi_tranceiver(0);
					}
					start = ((number[4]*1)+(number[3]*10)+(number[2]*100)+(number[1]*1000)+(number[0]*10000));
					
					for ((n=start),(q=0);(n<(start+16))&&(buffer!=1)&&(buffer!='N')&&(q<16);n++,q++)
					{
						buffer=spi_tranceiver(0);
						EEWriteByte(n,buffer);
						_delay_ms(10);
						
					}
			
					for ((n=start),(q=0);(n<(start+16))&&(q<16);n++,q++)
					{
						EEReadByte(n, &hihi);
						
					}
					
				}
			}
			else if (buffer=='g')
			{
				RTC_Get_Time();
				RTC_Get_Date();
				spi_tranceiver(second);
				spi_tranceiver(mint);
				spi_tranceiver(hour);
				spi_tranceiver(day);
				spi_tranceiver(month);
				spi_tranceiver(year);
			
			}
				
			
			else if (buffer=='h')
			{
				for (m=32;m<1024;m++)
				{
					EEWriteByte(m,255);
					_delay_ms(10);
					
				}
				eeprom_write_word ((uint16_t*)65520, 32);
			}
			
			
	}
}
