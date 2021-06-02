
#include "common.h"

uint8_t BIO_COUNT(void)
{
  uint8_t count=0;
	I2C_start_com(1,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x07);					
	I2C_stop_com();
	I2C_start_com(1,BIO_slv_add,1);
	count = I2C_read();
	I2C_stop_com();
	
	if(count>=100)
	{
		return 1;
	}
	else return 0;
}

void BIO_read_dataword(uint8_t *pointer){
	
	I2C_start_com(1,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x08);					
	I2C_stop_com();
	I2C_start_com(3,BIO_slv_add,1);
	*pointer		 = I2C_read();
	*(pointer+1) = I2C_read();
	*(pointer+2) = I2C_read();
	I2C_stop_com();
}

void BIO_init(void){
	
//	GPIOA ->BSRR |= GPIO_BSRR_BS5;
	
	enable_MAXM86161;
	
	//--- RESET FOR INITIALISATION---------------------------------
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x0D);					
	I2C_write(0x01);
	I2C_stop_com();		//WRITE RESET to Register 0x0D to initiate a software Reset 
	
	unsigned int i = 0;
	for(i=0; i<40000; i++){}	// Delay about 1ms to ensure the Reset being complete
		
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x0D);					
	I2C_write(0x02);
	I2C_stop_com();		//WRITE SHDN to Register 0x0D to shut down the Sensor for changing the Register values 
		
		//--- CLEAR INTERRUPTS-----------------------------------------		
	I2C_start_com(1,BIO_slv_add,0);
	I2C_write(0x00);
	I2C_stop_com();
	I2C_start_com(1,BIO_slv_add,1);
	I2C_read();
	I2C_stop_com(); //READ STATUS 1 to clear all interrupts 
		
	I2C_start_com(1,BIO_slv_add,0);
	I2C_write(0x01);
	I2C_stop_com();
	I2C_start_com(1,BIO_slv_add,1);
	I2C_read();
	I2C_stop_com(); //READ STATUS 2 to clear all interrupts 
		
	//--- AFE SETTING WRITE ----------------------------------------------	
	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x11);
	I2C_write(0x0B);
	I2C_stop_com(); // SET PPG_TINT[1:0] to 0x3 for a pulse width = 123.8ms, SET PPG2_PPG+ADC_RGE[3:2] to 0x2 for an ADC range = 16uA

	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x12);
	I2C_write(0x00);
	I2C_stop_com(); //Clear SMP_AVE and PPG_SR for a Samplerate = 25sps
	
	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x13);
	I2C_write(0xC0);
	I2C_stop_com(); //LED_SETLNG to 0x3 for a LED settling Time = 12us
	
  I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x15);
	I2C_write(0x01);
	I2C_stop_com(); //Photodioe Biasing = 0~65pF
	
//	//--- AFE SETTING READ----------------------------------------------	
//	
//	I2C_start_com(1,BIO_slv_add,0);
//	I2C_write(0x11);
//	I2C_stop_com();
//	I2C_start_com(4,BIO_slv_add,1);
//	I2C_read();
//	I2C_read();
//	I2C_read();
//	I2C_read();
//	I2C_stop_com();

		//--- LED DRIVER SETTINGS-------------------------------------
	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x2A);
	I2C_write(0x3A);
	I2C_stop_com(); // All LED DRIVER Ranges = 124mA
	
	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x23);
	I2C_write(0x20);
	I2C_stop_com(); //LED DRIVER 1 Current = 15.36mA
	
	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x24);
	I2C_write(0x20);
	I2C_stop_com(); //LED DRIVER 2 Current = 15.36mA
	
	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x25);
	I2C_write(0x20);
	I2C_stop_com(); //LED DRIVER 3 Current = 15.36mA
	
	//--- LOW POWER MODE ---------------------------------
//	I2C_start_com(2,BIO_slv_add,0);
//	I2C_write(0x0D);
//	I2C_write(0x06);
//	I2C_stop_com(); //ENABLE LOW POWER MODE but keep SHDN
	
	//--- FIFO CONFIGURATIONS ----------------------------
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x09);					
	I2C_write(0x00);
	I2C_stop_com();		//WRITE 0x08 to the FIFO_A_FULL Register. 
										//Almost Full interrupt will be triggered 8 entries before FIFO is full
										
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x0A);					
	I2C_write(0x01);
	I2C_stop_com();		//ENABLE FIFO_STAT_CLEAR (cleares the A_FULL and DATA_RDY interrupts on a FIFO_DATA register read)
										//ENABLE A_FULL_TYPE (A_FULL interrupt does not occure for every new Data onely if a new A_FULL condition is reached)

	//--- INTERRUPTS --------------------------------------
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C2 communication
	I2C_write(0x02);					
	I2C_write(0x00); //Enable almost Full interrupt
	I2C_stop_com();
		
	//--- LED Sequence Register ---------------------------
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C2 communication
	I2C_write(0x20);					
	I2C_write(0x01);
	I2C_stop_com();			//LEDC1[3:0] for LED1 and LEDC2[7:4] for LED2
	
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C2 communication
	I2C_write(0x21);
	I2C_write(0x00); 		 
	I2C_stop_com(); 		//LEDC3[3:0] for LED3 and LEDC4[7:4] for DIRECT AMBIENT
	
	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x0D);
	I2C_write(0x00);
	I2C_stop_com(); //Disable SHDN 
}