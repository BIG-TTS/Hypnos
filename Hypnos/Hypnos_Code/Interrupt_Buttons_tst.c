/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Interrupt Button test file, turns motor on and off
Datum: 14.11.2020
-------------------------------------*/

#include <stm32l431xx.h>
#include "system_init.h"
#include "GPIO.h"

int main(void)	//main
{
	system_clock_init();	//Initiliaze RCC and clocks
	GPIO_init();	//Initiliaze GPIOs
	
	//Enable Interrupt for Button 1 and 2
	GPIOA ->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1);	//Configure PA0 and PA1 as Input
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1);	//No pull up or pull down	
	
	SYSCFG ->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI0_Msk | SYSCFG_EXTICR1_EXTI1_Msk);	//Line Mapping
	
	EXTI ->IMR1 |= (EXTI_IMR1_IM0 | EXTI_IMR1_IM1);	//Unmask PA0 and PA1 for Interrupt line
	EXTI ->RTSR1 |= (EXTI_RTSR1_RT0 | EXTI_RTSR1_RT1);	//Detect rising edge
	
	
	NVIC_EnableIRQ(EXTI0_IRQn);	//Enable interrupt for EXTI0
	NVIC_EnableIRQ(EXTI1_IRQn);	//Enable interrupt for EXTI1

	
	while(1)	//endless loop
	{
		
	}
}
//Button 1
void EXTI0_IRQHandler(void)
{
	EXTI ->PR1 |= EXTI_PR1_PIF0;	//reset interrupt flag
	set_motor_ctrl;	//turn motor on
}
//Button 2
void EXTI1_IRQHandler(void)
{
	EXTI ->PR1 |= EXTI_PR1_PIF1;	//reset interrupt flag
	reset_motor_ctrl;	//turn motor off
}
