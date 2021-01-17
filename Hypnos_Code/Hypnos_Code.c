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
	
	USART_write(1);
	USART_write(2);
	USART_write(3);
	
	while(1)	//endless loop
	{

	}
}
