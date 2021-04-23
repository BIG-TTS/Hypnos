#include "COMMON.h"
#include "I2C.h"

/*------------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Header file for I2C2
Datum: 14.11.2020
-------------------------------------*/

void I2C_stop_com(void)	//Stop I2C2 communication
{
	while(!(I2C2 ->ISR & I2C_ISR_TC));	//Wait until last byte has been read/transfered (TC = 1)
	I2C2 ->CR2 |= I2C_CR2_STOP;	//Send stop condition
}
unsigned char I2C_read(void)	//Read data on I2C2 line
{
	unsigned char I2C_rx_data;	//data buffer
	while(!(I2C2 ->ISR & I2C_ISR_RXNE));	//wait until new data arrived
	I2C_rx_data = I2C2 ->RXDR;	//read data	
	return (I2C_rx_data);	//return received data
}
void I2C_write(unsigned char I2C_tx_data)	//Write data into I2C2 line
{
	while(!(I2C2 ->ISR & I2C_ISR_TXE));	//Wait until last data has been sent
	I2C2 ->TXDR = I2C_tx_data;	//Send new data
}
void I2C_start_com(unsigned char nBytes, unsigned char slave_addr, unsigned char r_w)	//Start or Restart I2C2 communication
{
	while(((I2C2 ->ISR & I2C_ISR_BUSY) >>I2C_ISR_BUSY_Pos) ^ ((I2C2 ->ISR & I2C_ISR_TC) >>I2C_ISR_TC_Pos));	//Start condition only send if bus is free or communicatio has stopped
	I2C2 ->CR2 &= ~(I2C_CR2_SADD | I2C_CR2_RD_WRN | I2C_CR2_NBYTES);	//Reset Slave Address, Read/Write and NBYTES register
	I2C2 ->CR2 |= (slave_addr <<1);	//Write slave address into SADD register
	I2C2 ->CR2 |= (r_w <<I2C_CR2_RD_WRN_Pos);	//Select read or write mode	(1 for read)
	I2C2 ->CR2 |= (nBytes <<I2C_CR2_NBYTES_Pos);	//Set number of Bytes to be read/transfered
	I2C2 ->CR2 &= ~(I2C_CR2_RELOAD);	//Clear Reload bit
	I2C2 ->CR2 &= ~(I2C_CR2_AUTOEND);	//Clear Auto End bit
	I2C2 ->CR2 |= I2C_CR2_START;	//Send start condition
}

void I2C_init(void)	//Initialization of I2C2
{
	RCC ->APB1ENR1 |= RCC_APB1ENR1_I2C2EN;	//Enable I2C2 peripheral clock
	I2C2 ->CR1 &= ~(I2C_CR1_PE);	//Disable I2C2 
	I2C2 ->TIMINGR |= 0x00702991; //Configure Timing (calculated by Cube)
	I2C2 ->CR1 |= I2C_CR1_PE;	//Enable I2C2
}
