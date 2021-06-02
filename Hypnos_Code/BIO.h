	
	
	#ifndef BIO__H
	#define BIO__H
	
	#include "common.h"
	
	#define BIO_slv_add 0x62
	#define enable_MAXM86161 		(GPIOA ->BSRR |= GPIO_BSRR_BS5)
	
	void BIO_init(void);
	
	void BIO_read_dataword(uint8_t *pointer);
	
	uint8_t BIO_COUNT(void);
	
 #endif
 