/*-----------------------------------
Author: Marco Rouge / Andrin Kälin
Arbeit: Hypnos
Thema: Header for Biosensor configuration
Datum: 17.01.2021
-------------------------------------*/

#include "COMMON.h"
#include "BIO_Init.h"

void BIO_read(unsigned char *ArrayPointer)
{
	unsigned int value = 0;
	I2C_start_com(1,BIO_slv_add,0); //Start I2C2 communication
	I2C_write(0x08);	//tells sensor to read from Register 0x08
	I2C_stop_com();
	I2C_start_com(3,BIO_slv_add,1); //repeated start
	
	for(value = 0; value<3; value++){ //read 3 Bytes to the Array given to the function
	*(ArrayPointer + value) = I2C_read();
	}
	I2C_stop_com();
}

void BIO_init(void)
{
//	//Enable Interrupt on PA6 (connected to Int.Pin)//
//	
//	//Setup IOs//
//	GPIOA ->MODER &= ~(GPIO_MODER_MODE6);	//Configure PA6 as Input
//	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD6);	//Reset PUPDR of PA6
//	GPIOA ->PUPDR |= GPIO_PUPDR_PUPD6_0;	//Set Pull Up Resistor for PA6
//	GPIOA ->OSPEEDR |= 0x3000;
//	GPIOA ->OTYPER &= ~GPIO_OTYPER_OT6;
//	
//	//Map PA6 to interrupt line 6//
//	SYSCFG ->EXTICR[1] &= ~(SYSCFG_EXTICR2_EXTI6_PA);	//Line Mapping
//	
//	//Set up Interrupt on PA6//
//	EXTI ->IMR1 |= (EXTI_IMR1_IM6);	//Unmask PA6 for Interrupt line
//	EXTI ->EMR1 |= (EXTI_EMR1_EM6);	//Unmask PA6 for Interrupt line
//	EXTI ->FTSR1 |= EXTI_FTSR1_FT6;	//Detect falling edge on EXTI2
//	
//	//Enable Interrupt//
//	__enable_irq();
//	
//	NVIC_SetPriority(EXTI9_5_IRQn,4); //Set priority
//	
//  NVIC_ClearPendingIRQ(EXTI9_5_IRQn); //clear pending
//	
//  NVIC_EnableIRQ(EXTI9_5_IRQn); ///enable interrupt
//		
//	//Do not forget to clear the EXTI_PR1 bit by writing a 1 to it in the ISR//
	
	set_LDO_EN;	

	//--- RESET FOR INITIALISATION---------------------------------
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x0D);
	I2C_write(0x01);
	I2C_stop_com();		//WRITE RESET to Register 0x0D to initiate a software Reset 
	
	//unsigned int i = 0;
 	//for(i=0; i<28000; i++){}	// Delay about 1ms to ensure the Reset being complete
		
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
		
	//--- AFE SETTING----------------------------------------------		
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
	
	//--- FIFO CONFIGURATIONS ----------------------------
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x09);					
	I2C_write(0x0F);
	I2C_stop_com();		//WRITE 0x0F to the FIFO_A_FULL Register. 
										//Almost Full interrupt will be triggered 15 entries before FIFO is full
										
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C communication
	I2C_write(0x0A);					
	I2C_write(0x0A);
	I2C_stop_com();		//ENABLE FIFO_STAT_CLEAR (cleares the A_FULL and DATA_RDY interrupts on a FIFO_DATA register read)
										//ENABLE A_FULL_TYPE (A_FULL interrupt does not occure for every new Data onely if a new A_FULL condition is reached)

	//--- INTERRUPTS --------------------------------------
//	I2C_start_com(2,BIO_slv_add,0);	//Start I2C2 communication
//	I2C_write(0x02);					
//	I2C_write(0x80);
//	I2C_stop_com(); //Enable A_Full interrupt 
		
	//--- LED Sequence Register ---------------------------
	I2C_start_com(2,BIO_slv_add,0);	//Start I2C2 communication
	I2C_write(0x20);					
	I2C_write(0x91);
	I2C_stop_com();			//LEDC1[3:0] for LED1 and LEDC2[7:4] for LED2
	
//	I2C_start_com(2,BIO_slv_add,0);	//Start I2C2 communication
//	I2C_write(0x21);
//	I2C_write(0x93); 		 
//	I2C_stop_com(); 		//LEDC3[3:0] for LED3 and LEDC4[7:4] for DIRECT AMBIENT
	
	//--- LOW POWER MODE ---------------------------------
	I2C_start_com(2,BIO_slv_add,0);
	I2C_write(0x0D);
	I2C_write(0x04);
	I2C_stop_com(); //ENABLE LOW POWER MODE and disable SHDN
	

}
