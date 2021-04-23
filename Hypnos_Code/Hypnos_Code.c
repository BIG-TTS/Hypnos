/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Main File
Datum: 14.11.2020
-------------------------------------*/

#include "COMMON.h"

int main(void)	//main
{	
	//---Initialisation-------------------------------$
	system_clock_init();	//Initiliaze RCC and clocks
	GPIO_init();
	I2C_init();
	USART_init();
	BIO_init();
	//------------------------------------------------$
	
	//--- Variables-----------------------------------$
	unsigned int Data = 0;
	unsigned int i = 0;
	unsigned char wByte[3] ;
	//------------------------------------------------$
//		USART_write('H');
//		USART_write('e');
//		USART_write('l');
//		USART_write('l');
//		USART_write('o');	
////	
		
		
	while(1)	//endless loop
	{
//		BIO_read(wByte);
//	Data = 4147894;
//	wByte = &((char)Data);
//		for(i=0; i<3 ; i++)
//			{
//				USART_write(*(wByte+i));
//			}

		USART_write(0x54);
		USART_write(0x77);
		USART_write(0x98);
	}
}


