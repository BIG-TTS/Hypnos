/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: I2C test file, reads data from the Accelerometer
Datum: 14.11.2020
-------------------------------------*/

#include <stm32l431xx.h>
#include "system_init.h"
#include "GPIO.h"
#include "I2C.h"

//Declaration of functions
int main(void)	//main
{
	unsigned char data = 0;	//data buffer
	
	system_clock_init();	//Initiliaze RCC and clocks
	GPIO_init();
	I2C_init();	//Initialiaze I2C2
	
	I2C_start_com(2,0x1C,0);	//start, 2 bytes, adress 0x1C, write
	I2C_write(0x2A);//write register address
	I2C_write(0x3);//write into register
	I2C_stop_com();//stop
	
	I2C_start_com(1,0x1C,0);//start
	I2C_write(0x01);//write register addres
	I2C_stop_com();//stop
	I2C_start_com(8,0x1C,1);//restart
	
	for(unsigned int i = ((I2C2 ->CR2 & I2C_CR2_NBYTES) >> I2C_CR2_NBYTES_Pos); i > 0; i--)	//Read as long as Bytes have to be read (nRead != nBytes)
	{
		data = I2C_read();
	}

	I2C_stop_com();
	
	while(1)	//endless loop
	{
	}
}
