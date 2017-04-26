/*
 * SPI_Driver.h
 *
 * Created: 12/21/2016 5:01:32 PM
 *  Author: salah yousef
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_
#define DD_SS     4
#define DD_MOSI   5
#define DD_MISO   6
#define DD_SCK    7
#define DD_SPI    DDRB

typedef struct
{
	unsigned char SPIINTERRUPT;
	unsigned char SPIEnable;
	unsigned char DataOrder;
	unsigned char MasterSlaveSelect;
	unsigned char SPIMode;
	unsigned char SCKRate;
	unsigned char DoubleSpeed;
}SPI;

typedef enum
{
	Slave =0,
	Master,
	Disaple =0,
	Enable ,
	Mode0 =0,
	Mode1,
	Mode2,
	Mode3,
	MSB_First=0,
	LSB_First,
	Fosc4 =0,
	Fosc16,
	Fosc64,
	Fosc128,
	Fosc2,
	Fosc8,
	Fosc32,
}config;

void SPI_MasterInit(SPI *Param_SPI);
void SPI_SlaveInit(SPI *Param_SPI);
char spi_tranceiver (unsigned char data);


#endif /* SPI_DRIVER_H_ */