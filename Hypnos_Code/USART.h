/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Header file for USART
Datum: 14.11.2020
-------------------------------------*/

#ifndef __USART__
#define __USART__

//--- FUNCTION HEADERS -------------------------$
void USART_init(void);	//Initialization of USART1
void USART_write(unsigned char usart_tx_data);	//Send data via USART1
unsigned char USART_read(void);	//Receive data via USART2
//--- FUNCTION HEADERS -------------------------$

//--- DEFINES ----------------------------------$

//--- DEFINES ----------------------------------$

#endif
