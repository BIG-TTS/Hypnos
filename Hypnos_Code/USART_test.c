/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Usart test file, sends a string to PC
Datum: 14.11.2020
-------------------------------------*/

#include <stm32l431xx.h>
#include <string.h>
#include "system_init.h"
#include "GPIO.h"
#include "USART.h"

int main(void)
{
	char string[] = "hello";
	
	system_clock_init();
	GPIO_init();
	USART_init();
	
	for(unsigned int i = 0; i < strlen(string);  i++)
	{
		USART_write(string[i]);
	}
}

