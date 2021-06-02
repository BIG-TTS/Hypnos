

#include "common.h"

void GPIO_init(void)
{
	//Enable GPIO clock
	RCC ->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;	//Enable Peripheral Clock for GPIOA
	RCC ->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;	//Enable Peripheral Clock for GPIOB
	
	//Configure all GPIOS in analog mode to lower current consumption
	//GPIOA ->MODER |= 0xFFFFFFFF;
	//GPIOB ->MODER |= 0xFFFFFFFF;
	
	//Initialization of GPIO Pins for USART1	
	GPIOA ->MODER &= ~(GPIO_MODER_MODE9 | GPIO_MODER_MODE10);	//Reset PA9 and PA10 modes
	GPIOA ->MODER |= (GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1);	//Configure PA9 and PA10 as alternate function
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT9 | GPIO_OTYPER_OT10);	//Configure PA9 and PA10 as push pull
	GPIOA ->OSPEEDR |= (GPIO_OSPEEDR_OSPEED9 | GPIO_OSPEEDR_OSPEED10);	//Configure speed to the maximum
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD9 | GPIO_PUPDR_PUPD10);	//No pull up or pull down
  GPIOA ->AFR[1] &= ~(GPIO_AFRH_AFSEL9 | GPIO_AFRH_AFSEL10);	//Reset alternate function mapping
	GPIOA ->AFR[1] |= (0x7 <<GPIO_AFRH_AFSEL9_Pos);	//Map PA9 to alternate function 7
	GPIOA ->AFR[1] |= (0x7 <<GPIO_AFRH_AFSEL10_Pos);	//Map PA10 to alternate function 7
	
	//Initialization of GPIO Pins for I2C 
	GPIOB ->MODER &= ~(GPIO_MODER_MODE11 | GPIO_MODER_MODE10);	//Reset PB11 and PB10 modes
	GPIOB ->MODER |= (GPIO_MODER_MODE11_1 | GPIO_MODER_MODE10_1);	//Configure PB11 and PB10 as alternate function
	GPIOB ->OTYPER |= (GPIO_OTYPER_OT11 | GPIO_OTYPER_OT10);	//Configure PB11 and PB10 as open drain
	GPIOB ->OSPEEDR |= (GPIO_OSPEEDR_OSPEED11 | GPIO_OSPEEDR_OSPEED10);	//Configure speed to the maximum
	GPIOB ->PUPDR &= ~(GPIO_PUPDR_PUPD11 | GPIO_PUPDR_PUPD10);	//No pull up or pull down
  GPIOB ->AFR[1] &= ~(GPIO_AFRH_AFSEL10 | GPIO_AFRH_AFSEL11);	//Reset alternate function mapping
	GPIOB ->AFR[1] |= (0x4 <<GPIO_AFRH_AFSEL10_Pos);	//Map PB10 to alternate function 4
	GPIOB ->AFR[1] |= (0x4 <<GPIO_AFRH_AFSEL11_Pos);	//Map PB11 to alternate function 4
	
	//Initialization of LDO_EN pin
	GPIOA ->MODER &= ~(GPIO_MODER_MODE5);	//Reset PA5 Mode
	GPIOA ->MODER |= GPIO_MODER_MODE5_0;	//Configure PA5 as output
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT5);	//Configure PA5 output as push-pull
	GPIOA ->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5);	//Configure speed to minimum
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD5);	//No pull up or pull down
	
	//Initialization of MOTOR_CTRL pin
	GPIOA ->MODER &= ~(GPIO_MODER_MODE8);	//Reset PA8 Mode
	GPIOA ->MODER |= GPIO_MODER_MODE8_0;	//Configure PA8 as output
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT8);	//Configure PA8 output as push-pull
	GPIOA ->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED8);	//Configure speed to minimum
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD8);	//No pull up or pull down
	
	//Initialization of EEPROM_WP pin
	GPIOB ->MODER &= ~(GPIO_MODER_MODE0);	//Reset PB0 Mode
	GPIOB ->MODER |= GPIO_MODER_MODE0_0;	//Configure PB0 as output
	GPIOB ->OTYPER &= ~(GPIO_OTYPER_OT0);	//Configure PB0 output as push-pull
	GPIOB ->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0);	//Configure speed to minimum
	GPIOB ->PUPDR &= ~(GPIO_PUPDR_PUPD0);	//No pull up or pull down
	
	//Initialization of display control pins (VPANEL_ON, VLOGIC_ON, RST, D/C)
	GPIOB ->MODER &= ~(GPIO_MODER_MODE12 | GPIO_MODER_MODE13 | GPIO_MODER_MODE14 | GPIO_MODER_MODE15);	//Reset PB12-PB15 Mode
	GPIOB ->MODER |= (GPIO_MODER_MODE12 | GPIO_MODER_MODE13 | GPIO_MODER_MODE14 | GPIO_MODER_MODE15);	//Configure PB12-PB15 as output
	GPIOB ->OTYPER &= ~(GPIO_OTYPER_OT12 | GPIO_OTYPER_OT13 | GPIO_OTYPER_OT14 | GPIO_OTYPER_OT15);	//Configure PB12-PB15 output as push-pull
	GPIOB ->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED12 | GPIO_OSPEEDR_OSPEED13 | GPIO_OSPEEDR_OSPEED14 | GPIO_OSPEEDR_OSPEED15);	//Configure speed to minimum
	GPIOB ->PUPDR &= ~(GPIO_PUPDR_PUPD12 | GPIO_PUPDR_PUPD13 | GPIO_PUPDR_PUPD14 | GPIO_PUPDR_PUPD15);	//No pull up or pull down	
	
	//tst
	GPIOA ->MODER &= ~(GPIO_MODER_MODE3);	//Reset PA5 Mode
	GPIOA ->MODER |= GPIO_MODER_MODE3_0;	//Configure PA5 as output
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT3);	//Configure PA5 output as push-pull
	GPIOA ->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED3);	//Configure speed to minimum
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD3);	//No pull up or pull down
}