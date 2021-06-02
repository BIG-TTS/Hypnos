/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Header file for USART
Datum: 14.11.2020
-------------------------------------*/
#ifndef USART__H
#define USART__H
#include "common.h"

void USART_init(void);	//Initialization of USART1

void USART_write(uint8_t usart_tx_data);	//Send data via USART1

uint8_t USART_read(void);	//Receive data via USART2


#endif
