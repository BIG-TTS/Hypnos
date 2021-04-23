/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Header file for USART
Datum: 14.11.2020
-------------------------------------*/
#include "COMMON.h"


void USART_init(void)	//Initialization of USART1
{
	RCC ->APB2ENR |= RCC_APB2ENR_USART1EN;	//Enable peripheral clock for USART1
	USART1 ->CR1 &= ~(USART_CR1_UE);	//Disable USART1
	USART1 ->CR1 &= ~(USART_CR1_M1 | USART_CR1_M0);	//Set word length to 1 start bit, 8 data bits
	USART1 ->CR2 &= ~(USART_CR2_STOP);	//Set 1 stop bit
	USART1 ->BRR &= ~(0xFFFF);	//Reset BRR register
	USART1 ->BRR |= 0x208D;	//Baudrate set to 9600 -> 80MHz/9600 = 0x208D
	USART1 ->CR1 |= USART_CR1_UE;	//Enable USART1
	USART1 ->CR1 |= USART_CR1_TE;	//Enable Transmission
	USART1 ->CR1 |= USART_CR1_RE;	//Enable Reception	
}
void USART_write(unsigned char usart_tx_data)	//Send data via USART1
{
	while(!(USART1->ISR & USART_ISR_TXE)); //Wait until TX line is free
	USART1 ->TDR = usart_tx_data;	//write new data into TX line
}
unsigned char USART_read(void)	//Receive data via USART2
{
	unsigned char usart_rx_data = 0;	//data buffer	
	while(!(USART1->ISR & USART_ISR_RXNE))	//wait until new data arrived
	usart_rx_data = USART1 ->RDR;	//read received data
	
	return(usart_rx_data);	//return read data
}
