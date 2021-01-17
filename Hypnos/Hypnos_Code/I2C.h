/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Header file for I2C2
Datum: 17.01.2021
-------------------------------------*/

#ifndef __I2C__
#define __I2C__

//--- FUNCTION HEADERS ----------------------------$
void I2C_stop_com(void);	//Stop I2C2 communication
unsigned char I2C_read(void);	//Read data on I2C2 line
void I2C_write(unsigned char I2C_tx_data);	//Write data into I2C2 line
void I2C_start_com(unsigned char nBytes, unsigned char slave_addr, unsigned char r_w);	//Start or Restart I2C2 communication
void I2C_init(void);	//Initialization of I2C2
//--- FUNCTION HEADERS ----------------------------$

//--- DEFINES -------------------------------------$

//--- DEFINES -------------------------------------$

#endif
