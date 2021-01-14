/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Main File
Datum: 14.11.2020
-------------------------------------*/

#include <stm32l431xx.h>
#include "system_init.h"
#include "GPIO.h"
#include "USART.h"

int main(void)	//main
{	
	system_clock_init();	//Initiliaze RCC and clocks
	GPIO_init();
	USART_init();
	
	
	while(1)	//endless loop
	{
		USART_write('h');
		USART_write('e');
		USART_write('l');
		USART_write('l');
		USART_write('o');	
	}
}
