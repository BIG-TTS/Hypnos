/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Main File
Datum: 14.11.2020
-------------------------------------*/

#include <stm32l431xx.h>
#include "system_init.h"
#include "I2C.h"
#include "GPIO.h"
#include "BIO.h"


int main(void)	//main
{	
	uint32_t i =0;
	uint8_t o =0;
	uint8_t BIO_DATA[100][3];
	for(i=0;i<128;i++)
	{
		for(o=0;o<3;o++)
		{
			BIO_DATA[i][o] = 0;
		}
	}
	uint8_t BIO_WORD[3];
	for(o=0;o<3;o++)
	{
		BIO_WORD[o]= 0;
	}
		
	uint32_t BIO_WORD_19 =0;
	uint8_t BIO_WRITE_VAL =0;
		
	system_clock_init();	//Initiliaze RCC and clocks
	GPIO_init();
	I2C_init();
	BIO_init();
	USART_init();

	while(1)	//endless loop
	{
		
		if(BIO_COUNT())
		{
			for(i=0;i<100;i++)
			{
				BIO_read_dataword(BIO_WORD);
				for(o=0; o<3;o++)
				{
					BIO_DATA[i][o] = BIO_WORD[o];
				}
			}
			
			
		}
	
//		for(i=0;i<500000;i++) {}
//		
//			 
//			BIO_read_dataword(BIO_WORD);
//			
////			for(o=0;o<3;o++)
////			{
////				BIO_DATA[i][o]=0;
////				BIO_DATA[i][o]=BIO_WORD[o];
////			}
////		}
////		for(i=0;i<128;i++) {
//			BIO_WORD_19 = 0;
//			BIO_WORD_19 = (BIO_WORD[0] | (BIO_WORD[1]<<8) |((BIO_WORD[2]&0x07)<<16));
//			
//			BIO_WRITE_VAL = (uint8_t)(((float)BIO_WORD_19/(float)524287)*255);
//			
//			
//			USART_write(BIO_WRITE_VAL);
//			USART_write(0xAB);
//			for(o=0;o<3;o++)
//			{
//				USART_write(BIO_WORD[o]);
//			}
			
//			
//		}
	}
}


void TIM2_IRQHandler(void)
{
	unsigned int data_capture = TIM2 ->CCR1;
	
	if(data_capture>0)
	{
		TIM2 ->SR &= ~(TIM_SR_CC1IF);
		//do short button stuff
	}
	else if(TIM2 ->SR & TIM_SR_UIF)
	{
		TIM2 ->SR &= ~(TIM_SR_UIF);
		//do long buttons utff
	}	
}
