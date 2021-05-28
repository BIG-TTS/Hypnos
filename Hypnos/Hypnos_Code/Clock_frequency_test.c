/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Clock frequency test file, generates 1MHz PWM
Datum: 14.11.2020
-------------------------------------*/

#include <stm32l431xx.h>
#include "system_init.h"

int main(void)	//main
{	
	system_clock_init();	//Initiliaze RCC and clocks
	
	//TIM 15 CH2 GPIO configuration
	RCC ->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;	//Enable Peripheral Clock for GPIOA
	
	GPIOA ->MODER &= ~(GPIO_MODER_MODE3);	//Reset PA3 mode
	GPIOA ->MODER |= (GPIO_MODER_MODE3_1);	//Configure PA3 as alternate function
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT3);	//Configure PA3 as push pull
	GPIOA ->OSPEEDR |= (GPIO_OSPEEDR_OSPEED3);	//Configure speed to the maximum
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD3);	//No pull up or pull down
  GPIOA ->AFR[0] &= ~(GPIO_AFRL_AFSEL3);	//Reset alternate function mapping
	GPIOA ->AFR[0] |= (0xE <<GPIO_AFRL_AFSEL3_Pos);	//Map PA3 to alternate function 14
	
	//Timer 15 CH2 PWM configuration
	RCC ->APB2ENR |= RCC_APB2ENR_TIM15EN;	//Enable peripberal clock for TIM15
	
	TIM15 ->CCMR1 |= TIM_CCMR1_OC2PE;	//Preload enable
	TIM15 ->CCMR1 |= (0x6 << TIM_CCMR1_OC2M_Pos);	//Configure TIM15 CH2 in PWM mode 1
	TIM15 ->CCER |= TIM_CCER_CC2E;	//Enable Channel 2 Output
	
	TIM15 ->PSC = 9; //Clock division = 10 (1+PSC) -> 80Mhz/10 = 8MHz clock frequency
	TIM15 ->ARR = 7;	//PWM Period = 8 Clock Cycles (0-7) -> 8Mhz/8 = 1Mhz PWM frequency
	TIM15 ->CCR2 = 4;	//PWM pulse time = 4 Clock Cycles (0-3) -> PWM Duty Cycle = 1:1
	
	TIM15 ->EGR |= TIM_EGR_UG;	//Generate update event to initialize registers	
	
	TIM15 ->BDTR |= TIM_BDTR_MOE;	//Main Output Enable
	TIM15 ->CR1 |= TIM_CR1_CEN;		//TIM15 enable
	
	while(1)	//endless loop
	{
		
	}
}
