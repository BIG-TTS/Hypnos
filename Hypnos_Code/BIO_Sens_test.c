/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Bio Sensor test file
Datum: 14.11.2020
-------------------------------------*/

#include <stm32l431xx.h>
#include "system_init.h"
#include "GPIO.h"
#include "I2C.h"

#define BIO_slv_add	0x62

unsigned int BIO_read(void);
void BIO_init(void);

int main(void)	//main
{
	system_clock_init();	//Initiliaze RCC and clocks
	GPIO_init();	//Initialiazes GPIOs
	I2C_init();	//Initialiaze I2C2
	
	set_LDO_EN;	//Enable Bio Sensor
	
	BIO_init();	//Initialize Bio Sensor
	
	while(1)	//endless loop
	{
		BIO_read();	//Read Bio Sensor
	}
}

unsigned int BIO_read(void)
{
	unsigned int value = 0;
	
	I2C_start_com(1,BIO_slv_add,0); //Start I2C2 communication
	I2C_write(0x08);
	I2C_stop_com();	//tells sensor to read from Register 0x08
	I2C_start_com(3,BIO_slv_add,1); //repeated start
	value |= I2C_read();
	value |= I2C_read() << 8 ;
	value |= I2C_read() << 16;
	I2C_stop_com();
	
	return value;
}
void BIO_init(void)
{
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C2 communication
	I2C_write(0x0A);					
	I2C_write(0x2A);
	I2C_stop_com();		//WRITE 0x2A to Adress 0x0A configures the FIFO 

	I2C_start_com(2,BIO_slv_add,0);	//Start I2C2 communication
	I2C_write(0x10);					
	I2C_write(0x80);
	I2C_stop_com();
		
	I2C_start_com(7,BIO_slv_add,0);	//Start I2C2 communication
	I2C_write(0x20);					
	I2C_write(0x21);
	I2C_write(0x93);
	I2C_write(0x00);
	I2C_write(0x0F);
	I2C_write(0x0F);
	I2C_write(0x0F);
	I2C_stop_com(); //configures the  LED sequence Registers	
}
