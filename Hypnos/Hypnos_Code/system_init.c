#include "COMMON.h"

/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Header fiel for system startup
Datum: 14.11.2020
-------------------------------------*/

void system_clock_init(void)	//Initialization of RCC and clocks
{
	//Power Configuration
	PWR ->CR1 |= PWR_CR1_VOS_0;	//Set voltage scaling range to 1 (VOS = 01)
	RCC ->APB1ENR1 |= RCC_APB1ENR1_PWREN;	//Enable power interface clock
	PWR ->CR1 |= PWR_CR1_DBP;	//Enable backup domain access
	
	//Flash Configuration
	FLASH ->ACR |= FLASH_ACR_ICEN;	//Enable instruction cache
	FLASH ->ACR |= FLASH_ACR_DCEN;	//Enable data cache
	FLASH ->ACR &= ~(FLASH_ACR_PRFTEN);	//Disable prefetch (Default)
	FLASH ->ACR &= ~(FLASH_ACR_LATENCY); //Reset flash latency
	FLASH ->ACR |= FLASH_ACR_LATENCY_4WS; 	//Set latecy to 4 wait states
	
	//LSE Configuration
  RCC ->BDCR &= ~(RCC_BDCR_LSEDRV);	//LSEDRV drive capabilty lower mode (default)
	RCC ->BDCR |= RCC_BDCR_LSEON;	//Turn LSE on (LSEON = 1)
	while(!(RCC->BDCR & RCC_BDCR_LSERDY));	//Wait until LSE is stable(LSERDY = 1)
	//RCC ->BDCR |= RCC_BDCR_LSECSSON;	//Enable clock security system (LSECSSON = 1)
	
	//MSI Configuration
	RCC ->CR |= RCC_CR_MSIRANGE_6;	// SET MSI Range to 4MHz (Default)
	RCC ->CR |= RCC_CR_MSIPLLEN;	//Set auto-calibration (MSIPLLEN = 1);
	RCC ->CR |= RCC_CR_MSION; //Turn on MSI (MSION = 1)
	while(!(RCC->CR & RCC_CR_MSIRDY));	//Wait until MSI is stable (MSIRDY = 1)

	//PLL Configuration
	RCC ->CR &= ~(RCC_CR_PLLON);	//Disbale PLL
	while(RCC ->CR & RCC_CR_PLLRDY);	//Wait until PLL is off
	RCC ->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC);	//Reset source selection
	RCC ->PLLCFGR |= RCC_PLLCFGR_PLLSRC_MSI;	//Select MSI as clock source for PLL
	RCC ->PLLCFGR &= ~(RCC_PLLCFGR_PLLM);	//Set division of input clock to 1  (Default)
	RCC ->PLLCFGR &= ~(RCC_PLLCFGR_PLLR);	//Set division of output clock to 2 (Default)
	RCC ->PLLCFGR &= ~(RCC_PLLCFGR_PLLN);	//Reset PLLN
	RCC ->PLLCFGR |= (0x28<<RCC_PLLCFGR_PLLN_Pos);	//Set Multiplicator of input clock to 40 (PLLN = 40)
	RCC ->CR |= RCC_CR_PLLON;	//Enable PLL
	while(!(RCC ->CR & RCC_CR_PLLRDY));	//Wait until PLL is ready
	RCC ->PLLCFGR |= RCC_PLLCFGR_PLLREN;	//Enable the clock output of the main PLL

	//System clock Configuration
	RCC ->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);	//Reset prescaler
	RCC ->CFGR |= RCC_CFGR_HPRE_DIV1; //AHB prescaler to division 1
	RCC ->CFGR |= RCC_CFGR_PPRE1_DIV1; //APB1 prescaler to division 1
	RCC ->CFGR |= RCC_CFGR_PPRE2_DIV1; //APB2 prescaler to division 1
	RCC ->CFGR |= RCC_CFGR_SW_PLL;		//Set PLL as system clock source	
	while((RCC ->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);	//Wait for confirmation of clock source change to PLL
}
