/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Header for GPIO configuration
Datum: 14.11.2020
-------------------------------------*/

#ifndef __GPIO__
#define __GPIO__

//--- FUNCTION HEADERS ----------------------------$
void GPIO_init(void);
//--- FUNCTION HEADERS ----------------------------$

//--- DEFINES -------------------------------------$
//Set GPIO pins high
#define set_LDO_EN							GPIOA ->BSRR |= GPIO_BSRR_BS5
#define set_motor_ctrl					GPIOA ->BSRR |= GPIO_BSRR_BS8
#define set_EEPROM_WP						GPIOB ->BSRR |= GPIO_BSRR_BS0
#define set_display_DC 					GPIOB ->BSRR |= GPIO_BSRR_BS12
#define set_display_RST					GPIOB ->BSRR |= GPIO_BSRR_BS13
#define set_display_VLOGIC			GPIOB ->BSRR |= GPIO_BSRR_BS14
#define set_display_VPANEL			GPIOB ->BSRR |= GPIO_BSRR_BS15
                                                       
//Reset GPIO pins low                                    
#define reset_LDO_EN						GPIOA ->BSRR |= GPIO_BSRR_BR5
#define reset_motor_ctrl				GPIOA ->BSRR |= GPIO_BSRR_BR8
#define reset_EEPROM_WP					GPIOB ->BSRR |= GPIO_BSRR_BR0
#define reset_display_DC 				GPIOB ->BSRR |= GPIO_BSRR_BR12
#define reset_display_RST				GPIOB ->BSRR |= GPIO_BSRR_BR13
#define reset_display_VLOGIC		GPIOB ->BSRR |= GPIO_BSRR_BR14
#define reset_display_VPANEL		GPIOB ->BSRR |= GPIO_BSRR_BR15

#define set_tst							GPIOA ->BSRR |= GPIO_BSRR_BS3
#define reset_tst						GPIOA ->BSRR |= GPIO_BSRR_BR3
//--- DEFINES -------------------------------------$

#endif
